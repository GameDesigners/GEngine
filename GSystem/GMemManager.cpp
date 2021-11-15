#include "GMemManager.h"
#include "GStackWalker.h"

using namespace GEngine::GSystem;

typedef BOOL(WINAPI* tFMiniDumpWriteDump)(
	IN HANDLE hProcess,
	IN DWORD ProcessId,
	IN HANDLE hFile,
	IN MINIDUMP_TYPE DumpType,
	IN CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, OPTIONAL
	IN CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, OPTIONAL
	IN CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam OPTIONAL);

typedef BOOL(WINAPI* tFSymInitialize)(
	IN HANDLE   hProcess,
	IN PSTR     UserSearchPath,
	IN BOOL     fInvadeProcess);

typedef BOOL(WINAPI* tFStackWalk64)(
	DWORD                             MachineType,
	HANDLE                            hProcess,
	HANDLE                            hThread,
	LPSTACKFRAME64                    StackFrame,
	PVOID                             ContextRecord,
	PREAD_PROCESS_MEMORY_ROUTINE64    ReadMemoryRoutine,
	PFUNCTION_TABLE_ACCESS_ROUTINE64  FunctionTableAccessRoutine,
	PGET_MODULE_BASE_ROUTINE64        GetModuleBaseRoutine,
	PTRANSLATE_ADDRESS_ROUTINE64      TranslateAddress);

typedef BOOL(WINAPI* tFSymFromAddr)(IN HANDLE hProcess,IN DWORD64 Address,OUT PDWORD64 Displacement,IN OUT PSYMBOL_INFO Symbol);
typedef BOOL(WINAPI* tFSymGetLineFromAddr64)(IN HANDLE hProcess,IN DWORD64 qwAddr,OUT PDWORD pdwDisplacement,OUT PIMAGEHLP_LINE64 Line64);
typedef DWORD(WINAPI* tFSymGetOptions)(VOID);
typedef DWORD(WINAPI* tFSymSetOptions)(IN DWORD SymOptions);
typedef PVOID(WINAPI* tFSymFunctionTableAccess64)(HANDLE  hProcess,DWORD64 AddrBase);
typedef DWORD64(WINAPI* tFSymGetModuleBase64)(IN HANDLE hProcess,IN DWORD64 qwAddr);

static tFMiniDumpWriteDump fnMiniDumpWriteDump = NULL;
static tFSymInitialize fnSymInitialize = NULL;
static tFStackWalk64 fnStackWalk64 = NULL;
static tFSymFromAddr fnSymFromAddr = NULL;
static tFSymGetLineFromAddr64 fnSymGetLineFromAddr64 = NULL;
static tFSymGetOptions fnSymGetOptions = NULL;
static tFSymSetOptions fnSymSetOptions = NULL;
static tFSymFunctionTableAccess64 fnSymFunctionTableAccess64 = NULL;
static tFSymGetModuleBase64 fnSymGetModuleBase64 = NULL;

static HMODULE s_DbgHelpLib = NULL;    //dbghelp.dll载入模块的对象
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

}

void* GDebugMem::Allocate(size_t uiSize, size_t uiAlignment, bool bIsArray)
{
	return nullptr;
}

void GDebugMem::Deallocate(char* pcAddr, unsigned int uiAlignment, bool bIsArray)
{

}



bool GDebugMem::InsertBlock(Block* pBlock)
{
	GASSERT(pBlock!=nullptr);
	if (m_pHeadBlock == nullptr && m_pTailBlock == nullptr)
	{
		m_pHeadBlock = pBlock;
		m_pTailBlock = pBlock;
		return true;
	}
	else if(m_pTailBlock!=nullptr)
	{
		m_pTailBlock->m_pNext = pBlock;
		pBlock->m_pPrev = m_pTailBlock;
		m_pTailBlock = pBlock;
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


/**
 *  加载dbghelp.dll
 */
bool GDebugMem::LoadDbgHelpLibrary()
{
	s_DbgHelpLib = LoadLibrary(TEXT("\\dbghelp.dll"));
	if (s_DbgHelpLib == nullptr)
	{
		s_DbgHelpLib= LoadLibrary(TEXT("dbghelp.dll"));
		if (s_DbgHelpLib == nullptr)
			return false;
	}

	fnMiniDumpWriteDump = (tFMiniDumpWriteDump)GetProcAddress(s_DbgHelpLib, "MiniDumpWriteDump");
	fnSymInitialize = (tFSymInitialize)GetProcAddress(s_DbgHelpLib, "SymInitialize");
	fnStackWalk64 = (tFStackWalk64)GetProcAddress(s_DbgHelpLib, "StackWalk64");
	fnSymFromAddr = (tFSymFromAddr)GetProcAddress(s_DbgHelpLib, "SymFromAddr");
	fnSymGetLineFromAddr64 = (tFSymGetLineFromAddr64)GetProcAddress(s_DbgHelpLib, "SymGetLineFromAddr64");
	fnSymGetOptions = (tFSymGetOptions)GetProcAddress(s_DbgHelpLib, "SymGetOptions");
	fnSymSetOptions = (tFSymSetOptions)GetProcAddress(s_DbgHelpLib, "SymSetOptions");
	fnSymFunctionTableAccess64 = (tFSymFunctionTableAccess64)GetProcAddress(s_DbgHelpLib, "SymFunctionTableAccess64");
	fnSymGetModuleBase64 = (tFSymGetModuleBase64)GetProcAddress(s_DbgHelpLib, "SymGetModuleBase64");

	if (fnMiniDumpWriteDump && fnSymInitialize && fnStackWalk64 && fnSymFromAddr && fnSymGetLineFromAddr64 && fnSymGetOptions && fnSymSetOptions && fnSymFunctionTableAccess64 && fnSymGetModuleBase64)
	{
		DWORD ProcessId = ::GetCurrentProcessId();
		s_Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
		fnSymInitialize(s_Process, (PSTR)".", TRUE);
		return true;
	}
	return false;
}

/**
 *  卸载dbghelp.dll
 */
bool GDebugMem::UninstallDbgHelpLibrary()
{
	if (s_DbgHelpLib != NULL)
	{
		FreeLibrary(s_DbgHelpLib);
		CloseHandle(s_Process);
		s_Process = NULL;
		s_DbgHelpLib = NULL;
	}

	fnMiniDumpWriteDump = NULL;
	fnSymInitialize = NULL;
	fnStackWalk64 = NULL;
	fnSymFromAddr = NULL;
	fnSymGetLineFromAddr64 = NULL;
	fnSymGetOptions = NULL;
	fnSymSetOptions = NULL;
	fnSymFunctionTableAccess64 = NULL;
	fnSymGetModuleBase64 = NULL;
	
	return true;
}

void GDebugMem::PrintMemCallAndReleaseLog()
{
	LoadDbgHelpLibrary();
	IMAGEHLP_LINE64 Line;
	Line.SizeOfStruct = sizeof(Line);
	memset(&Line, 0, sizeof(Line));
	DWORD Offset = 0;



	CONTEXT c;
	memset(&c, 0, sizeof(c));
	int frameNum;
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, GetCurrentThreadId());
	do {
		memset(&c, 0, sizeof(CONTEXT));
		c.ContextFlags = USED_CONTEXT_FLAGS;
		RtlCaptureContext(&c);
	} while (0);
	STACKFRAME64 s;
	memset(&s, 0, sizeof(s));
	DWORD imageType;
#ifdef _M_IX86
	imageType = IMAGE_FILE_MACHINE_I386;
	s.AddrPC.Offset = c.Eip;
	s.AddrPC.Mode = AddrModeFlat;
	s.AddrFrame.Offset = c.Ebp;
	s.AddrFrame.Mode = AddrModeFlat;
	s.AddrStack.Offset = c.Esp;
	s.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
	imageType = IMAGE_FILE_MACHINE_AMD64;
	s.AddrPC.Offset = c.Rip;
	s.AddrPC.Mode = AddrModeFlat;
	s.AddrFrame.Offset = c.Rsp;
	s.AddrFrame.Mode = AddrModeFlat;
	s.AddrStack.Offset = c.Rsp;
	s.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
	imageType = IMAGE_FILE_MACHINE_IA64;
	s.AddrPC.Offset = c.StIIP;
	s.AddrPC.Mode = AddrModeFlat;
	s.AddrFrame.Offset = c.IntSp;
	s.AddrFrame.Mode = AddrModeFlat;
	s.AddrBStore.Offset = c.RsBSP;
	s.AddrBStore.Mode = AddrModeFlat;
	s.AddrStack.Offset = c.IntSp;
	s.AddrStack.Mode = AddrModeFlat;
#else
#error "Platform not supported!"
#endif

	for (frameNum = 0;; frameNum++)
	{
		if (!StackWalk64(imageType, GetCurrentProcess(), GetCurrentThread(), &s, &c, MyReadProcMem, SymFunctionTableAccess64, SymGetModuleBase64, NULL))
			break;

		if (fnSymGetLineFromAddr64(s_Process, s.AddrPC.Offset, &Offset, &Line))
		{
			//TCHAR* filename = GPConstChar_To_PTCHAR(Line.FileName);
			wprintf(TEXT("泄露内存块  地址[%0x]  调用信息-->  文件名:%s  行数:%d\n"), Line.Address, Line.FileName, Line.LineNumber);
		}
		else
		{
			DWORD error = GetLastError();
			if (error == 487)
				GOutputDebugString(TEXT("未找到相关堆栈信息... [%ws]\n"), TEXT("No debug info in current module\n"));
			else if (error == 126)
				GOutputDebugString(TEXT("未找到相关堆栈信息... [%ws]\n"),TEXT("Debug info in current module has not loaded"));
			else
				GOutputDebugString(TEXT("未找到相关堆栈信息... [%ws]\n"), TEXT("SymGetLineFromAddr64 failed"));
		}

		if (s.AddrReturn.Offset == 0)
			break;
	}
	if (hThread != NULL && hThread != INVALID_HANDLE_VALUE)
		ResumeThread(hThread);
	UninstallDbgHelpLibrary();
}

BOOL GDebugMem::MyReadProcMem(HANDLE hProcess, DWORD64 qwBaseAddress, PVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead)
{
	SIZE_T st;
	BOOL bRet = ReadProcessMemory(hProcess, (LPVOID)qwBaseAddress, lpBuffer, nSize, &st);
	*lpNumberOfBytesRead = (DWORD)st;
	return TRUE;
}