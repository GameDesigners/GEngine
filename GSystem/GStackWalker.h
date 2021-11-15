#ifndef GSTACKWALKER_H
#define GSTACKWALKER_H
#include "GSystem.h"
#pragma  comment(lib,"dbghelp.lib")

namespace GEngine
{
	namespace GSystem
	{
#if defined(_M_IX86)
#ifdef CURRENT_THREAD_VIA_EXCEPTION
		// TODO: 下面使用异常的方式得到堆栈
#define GET_CURRENT_CONTEXT(c, contextFlags) \
  do { \
    memset(&c, 0, sizeof(CONTEXT)); \
    EXCEPTION_POINTERS *pExp = NULL; \
    __try { \
      throw 0; \
    } __except( ( (pExp = GetExceptionInformation()) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_EXECUTE_HANDLER)) {} \
    if (pExp != NULL) \
      memcpy(&c, pExp->ContextRecord, sizeof(CONTEXT)); \
      c.ContextFlags = contextFlags; \
  } while(0);
#else
		// 得到当前线程的线程上下文
#define GET_CURRENT_CONTEXT(c, contextFlags) \
  do { \
    memset(&c, 0, sizeof(CONTEXT)); \
    c.ContextFlags = contextFlags; \
    __asm    call x \
    __asm x: pop eax \
    __asm    mov c.Eip, eax \
    __asm    mov c.Ebp, ebp \
    __asm    mov c.Esp, esp \
  } while(0);
#endif

#else

// The following is defined for x86 (XP and higher), x64 and IA64:
#define GET_CURRENT_CONTEXT(c, contextFlags) \
  do { \
    memset(&c, 0, sizeof(CONTEXT)); \
    c.ContextFlags = contextFlags; \
    RtlCaptureContext(&c); \
} while(0);
#endif

		class GSYSTEM_API GStackWalker
		{
            #define USED_CONTEXT_FLAGS CONTEXT_FULL

		protected:
			static BOOL __stdcall MyReadProcMem(HANDLE hProcess, DWORD64 qwBaseAddress, PVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead);

			enum
			{
				STACKWALK_MAX_NAMELEN = 1024,
				STACK_MAX_RECORD = 32,
			};

			typedef struct CallstackEntry
			{
				DWORD64 offset;  // if 0, we have no valid entry
				CHAR FuncName[STACKWALK_MAX_NAMELEN];
				DWORD64 offsetFromSmybol;
				CHAR moduleName[STACKWALK_MAX_NAMELEN];
				DWORD64 baseOfImage;
				CHAR loadedImageName[STACKWALK_MAX_NAMELEN];
				CHAR ProcessImageName[MAX_PATH];
				DWORD64	ProcessEntryPoint;
				IMAGEHLP_LINE Lines;
			} CallstackEntry;

		public:
			GStackWalker(LPCSTR szSymPath = NULL, DWORD dwProcessId = GetCurrentProcessId(), HANDLE hProcess = GetCurrentProcess());
			~GStackWalker();
			BOOL InitSym(LPCSTR szSymPath);
			BOOL GetSymAndInitSym();

			DWORD LoadModule(HANDLE hProcess, LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size);
			BOOL LoadModules();
			BOOL ShowCallStack(HANDLE hProcess, DWORD dwThreadId);
			void ShowMessage(CallstackEntry cs);

			void GetStackFrameEntryAddressArray(HANDLE hProcess, DWORD dwThreadId, DWORD64 frames[STACK_MAX_RECORD]);
			void PrintCallStackFramesLog(DWORD64 frames[STACK_MAX_RECORD], HANDLE hProcess = NULL);

		protected:
			HANDLE  m_hProcess;
			DWORD	m_dwProcessId;
			BOOL    m_modulesLoaded;
			DWORD	m_dwThreadId;
			LPSTR	m_szSymPath;
		};
	}
}

#endif // !GSTACKWALKER_H
