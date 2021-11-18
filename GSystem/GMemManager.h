#ifndef GMEMMANAGER_H
#define GMEMMANAGER_H
#include "GSystem.h"

namespace GEngine
{
	namespace GSystem
	{
		class GSYSTEM_API GMemManager
		{
		public:
			virtual void* Allocate(size_t uiSize, size_t uiAlignment, bool bIsArray) = 0;
			virtual void Deallocate(char* pcAddr, unsigned int uiAlignment, bool bIsArray) = 0;
		};

		class GSYSTEM_API GDebugMem : public GMemManager 
		{
		public:
			GDebugMem();
			~GDebugMem();
			virtual void* Allocate(size_t uiSize, size_t uiAlignment, bool bIsArray);
			virtual void Deallocate(char* pcAddr, unsigned int uiAlignment, bool bIsArray);

		private:
			enum : unsigned int
			{
				MEM_BEGIN_MASK = 0xDEADC0DE,
				MEM_END_MASK = 0xDEADC0DE,
				RECORD_NUM = 64,
				CALLSTACK_NUM = 64
			};

			class Block
			{
			public:
				Block()
				{
					for (size_t i = 0; i < CALLSTACK_NUM; ++i)
						pCallStackRecords[i] = NULL;
					
					m_uiStackInfoNum = 0;
					m_uiMemSize = 0;
					m_bIsArray = false;
					m_bAlignment = false;

					m_pPrev = nullptr;
					m_pNext = nullptr;
				}

				DWORD64  pCallStackRecords[CALLSTACK_NUM];
				size_t   m_uiStackInfoNum;
				size_t   m_uiMemSize;
				bool     m_bIsArray;
				bool     m_bAlignment;

				Block* m_pPrev;
				Block* m_pNext;

			};

		public:
			void PrintMemCallAndReleaseLog();
		private:
			size_t m_uiNumNewCalls;                //New���õĴ���
			size_t m_uiNumDeleteCalls;             //Delete���õĴ���
			size_t m_uiNumCurrentBlocks;           //��ǰ�ڴ�������
			size_t m_uiNumBytes;                   //��ǰ������ڴ��С��byte��
			size_t m_uiMaxNumBytesInRecord;        //���������ڴ��Ĵ�С
			size_t m_uiMaxNumBlocksInRecord;       //�ڴ�������ķ�ֵ
			size_t m_uiSizeRecords[RECORD_NUM];    //�ڴ���Сɢ��

			Block* m_pHeadBlock;
			Block* m_pTailBlock;
			bool InsertBlock(Block* pBlock);
			bool RemoveBlock(Block* pBlock);
		};

		class GSYSTEM_API GMemObject
		{
		public:
			GMemObject() {}
			~GMemObject() {}

			static GMemManager& GetMemManager();
		};
	}
}

//�����ڴ���������
FORCEINLINE void* operator new(size_t uiSize)
{
	return GEngine::GSystem::GMemObject::GetMemManager().Allocate((unsigned int)uiSize, 0, false);
}

FORCEINLINE void operator delete(void* pcAddr)
{
	return GEngine::GSystem::GMemObject::GetMemManager().Deallocate((char*)pcAddr, 0, false);
}

FORCEINLINE void* operator new[](size_t uiSize)
{
	return GEngine::GSystem::GMemObject::GetMemManager().Allocate((unsigned int)uiSize, 0, true);
}

FORCEINLINE void operator delete[](void* pcAddr)
{
	return GEngine::GSystem::GMemObject::GetMemManager().Deallocate((char*)pcAddr, 0, true);
}



#endif // !GMEMMANAGER_H
