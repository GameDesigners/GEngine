#include "GMemManager.h"
#include "GStackWalker.h"

using namespace GEngine::GSystem;

static HANDLE  s_Process = NULL;


GDebugMem::GDebugMem()
{
	m_uiNumNewCalls = 0;
	m_uiNumDeleteCalls = 0;
	m_uiNumCurrentBlocks = 0;
	m_uiNumBytes = 0;
	m_uiMaxNumBytesInRecord = 0;
	m_uiMaxNumBlocksInRecord = 0;
	
	for (size_t i = 0; i < RECORD_NUM; i++)
		m_uiSizeRecords[i] = 0;

	m_pHeadBlock = nullptr;
	m_pTailBlock = nullptr;
}

GDebugMem::~GDebugMem()
{
	PrintMemCallAndReleaseLog();
}

void* GDebugMem::Allocate(size_t uiSize, size_t uiAlignment, bool bIsArray)
{
	size_t allocSize = sizeof(unsigned int) + uiSize + sizeof(unsigned int) + sizeof(Block);
	char* pAddr = (char*)malloc(allocSize);

	if (pAddr != nullptr)
	{
		//成功分配内存

		//处理第一段数据---->Block
		Block* block = (Block*)pAddr;
		
		//GStackWalker sw(NULL, GetCurrentProcessId(), GetCurrentProcess());		//获取此处分配内存的堆栈地址并记录到Block中
		//if (sw.GetSymAndInitSym() == FALSE || sw.LoadModules() == FALSE)
		//	GOutputDebugString(TEXT("GetSymAndInitSym Or LoadModules Fail"));
		//else 
		//{
		//	DWORD64 frameAddrs[CALLSTACK_NUM] = { NULL };
		//	sw.GetStackFrameEntryAddressArray(GetCurrentProcess(), GetCurrentThreadId(), frameAddrs);
		//	sw.PrintCallStackFramesLog(frameAddrs);
		//	size_t numStackCallLayer = 0;
		//	while (frameAddrs[numStackCallLayer] != NULL && numStackCallLayer < CALLSTACK_NUM)
		//	{
		//		block->pCallStackRecords[numStackCallLayer] = frameAddrs[numStackCallLayer];
		//		numStackCallLayer++;
		//	}
		//	block->m_uiStackInfoNum = numStackCallLayer;
		//}
		
		block->m_uiMemSize = uiSize;
		block->m_bIsArray = bIsArray;
		block->m_bAlignment = uiAlignment > 0 ? true : false;
		InsertBlock(block);

		//处理第一段数据---->内存块起始标记
		pAddr += sizeof(Block);
		unsigned int* pBeginMask = (unsigned int*)pAddr;
		*pBeginMask = MEM_BEGIN_MASK;

		//处理第二段数据---->真正内存的起始地址
		pAddr += sizeof(unsigned int);
		void* memory = (void*)(pAddr);

		//处理第三段数据---->内存块结束标记
		pAddr += uiSize;
		unsigned int* pEndMask = (unsigned int*)pAddr;
		*pEndMask = MEM_END_MASK;


		//更新内存Debug数据
		m_uiNumNewCalls++;
		m_uiNumCurrentBlocks++;
		m_uiNumBytes += uiSize;
		m_uiMaxNumBytesInRecord = m_uiMaxNumBytesInRecord < uiSize ? uiSize : m_uiMaxNumBytesInRecord;
		m_uiMaxNumBlocksInRecord = m_uiMaxNumBlocksInRecord < m_uiNumCurrentBlocks ? m_uiNumCurrentBlocks : m_uiMaxNumBlocksInRecord;
		for (size_t i = 0, size = 1; i < RECORD_NUM; i++, size <<= 1)
		{
			if (uiSize <= size) {
				m_uiSizeRecords[i]++;
				break;
			}
		}

		return memory;
	}
	else
	{
		GOutputDebugString(TEXT("malloc memory fail..."));
		return nullptr;
	}
}

void GDebugMem::Deallocate(char* pcAddr, unsigned int uiAlignment, bool bIsArray)
{
	//释放前进行内存验证。只有所有参数正确的时候才能进行释放操作
	//若验证失败，程序则会Crash...
	GASSERT(pcAddr);
	char* pAddr = pcAddr - (sizeof(unsigned int) + sizeof(Block));
	Block* pBlock = (Block*)pAddr;
	GASSERT(pBlock != nullptr);
	GASSERT((*(unsigned int*)(pcAddr - sizeof(unsigned int))) == MEM_BEGIN_MASK);
	GASSERT((*(unsigned int*)(pcAddr + pBlock->m_uiMemSize)) == MEM_END_MASK);
	GASSERT(pBlock->m_bAlignment == (uiAlignment > 0 ? true : false));
	GASSERT(pBlock->m_bIsArray == bIsArray);

	//验证通过，释放内存
	RemoveBlock(pBlock);
	m_uiNumCurrentBlocks--;
	m_uiNumDeleteCalls++;
	m_uiNumBytes -= pBlock->m_uiMemSize;

	free(pAddr);
}

bool GDebugMem::InsertBlock(Block* pBlock)
{
	GASSERT(pBlock!=nullptr);
	if (m_pHeadBlock == nullptr && m_pTailBlock == nullptr)
	{
		m_pHeadBlock = pBlock;
		m_pTailBlock = pBlock;
		pBlock->m_pNext = nullptr;
		pBlock->m_pPrev = nullptr;
		return true;
	}
	else if(m_pTailBlock!=nullptr)
	{
		m_pTailBlock->m_pNext = pBlock;
		pBlock->m_pPrev = m_pTailBlock;
		m_pTailBlock = pBlock;
		m_pTailBlock->m_pNext = nullptr;
		return true;
	}
	return false;
}

bool GDebugMem::RemoveBlock(Block* pBlock)
{
	GASSERT(pBlock != nullptr);
	if (pBlock == m_pHeadBlock)
	{
		m_pHeadBlock = pBlock->m_pNext;
		m_pHeadBlock->m_pPrev = nullptr;
		return true;
	}
	else if (pBlock == m_pTailBlock)
	{
		m_pTailBlock = m_pTailBlock->m_pPrev;
		m_pTailBlock->m_pNext = nullptr;
		return true;
	}
	else
	{
		pBlock->m_pPrev->m_pNext = pBlock->m_pNext;
		pBlock->m_pNext->m_pPrev = pBlock->m_pPrev;
		return true;
	}
}

void GDebugMem::PrintMemCallAndReleaseLog()
{
	if (m_pHeadBlock != nullptr)
	{
		//GStackWalker sw(NULL, GetCurrentProcessId(), GetCurrentProcess());
		//if (sw.GetSymAndInitSym() == FALSE || sw.LoadModules() == FALSE)
		//	GOutputDebugString(TEXT("GetSymAndInitSym Or LoadModules Fail"));
		//else 
		//{
		//	//存在内存泄漏问题,打印泄漏内存分配时的堆栈记录
		//	Block* current = m_pHeadBlock;
		//	while (current != nullptr)
		//	{
		//		sw.PrintCallStackFramesLog(current->pCallStackRecords);
		//		current = current->m_pNext;
		//	}
		//}
		Block* current = m_pHeadBlock;
		while (current != nullptr)
		{
			//sw.PrintCallStackFramesLog(current->pCallStackRecords);
			GOutputDebugString(TEXT("有一处内存泄漏\n"));
			current = current->m_pNext;
		}
	}
}



GMemManager& GMemObject::GetMemManager()
{
	static GDebugMem g_debugMem;
	return g_debugMem;
}