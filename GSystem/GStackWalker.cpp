#include "GStackWalker.h"
#include <TlHelp32.h>
#include <stdio.h>
using namespace GEngine::GSystem;

BOOL GStackWalker::MyReadProcMem(HANDLE hProcess, DWORD64 qwBaseAddress, PVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead)
{
	SIZE_T st;
	BOOL bRet = ReadProcessMemory(hProcess, (LPVOID)qwBaseAddress, lpBuffer, nSize, &st);
	*lpNumberOfBytesRead = (DWORD)st;
	return TRUE;
}


GStackWalker::GStackWalker(DWORD dwThreadId, LPCSTR szSymPath)
{
	m_dwThreadId = dwThreadId!=NULL?dwThreadId:GSystem::GetMainThreadID();
	m_szSymPath = szSymPath != NULL ? _strdup(szSymPath) : NULL;
	m_hProcess = ::GetCurrentProcess();
	m_dwProcessId = ::GetCurrentProcessId();
	m_modulesLoaded = FALSE;
	m_bInitalizeSuc = false;

	Initialize();
}

GStackWalker::~GStackWalker()
{
	if (m_szSymPath != NULL)
		free(m_szSymPath);
	m_szSymPath = NULL;
}


VOID GStackWalker::Initialize()
{
	m_bInitalizeSuc = GetSymAndInitSym() == TRUE && LoadModules() == TRUE;
	if (!m_bInitalizeSuc)
		GOutputDebugString(TEXT("GetSymAndInitSym Or LoadModules Fail"));
}

/**
 * 当SymInitialize 第三个参数为FALSE，手动调用SymLoadModule64 函数加载模块，
 * 此时第一个参数为任意非唯一的数值，用于标志符号
 * 否则 第一个 hProcess 必须为进程句柄，自动加载进程的所有模块的调试符号，
 * SymInitialize 使用UserSearchPath 指定的路径找符号文件多个路径以分号(;)分割
 */
BOOL GStackWalker::InitSym(LPCSTR szSymPath)
{
	if (szSymPath != nullptr)
		m_szSymPath = _strdup(szSymPath);

	if (SymInitialize(m_hProcess, m_szSymPath, FALSE) == FALSE)
	{
		GOutputDebugString(TEXT("m_szSymPath:%s\r\nGetLastError:%d\r\n"), m_szSymPath, GetLastError());
		return FALSE;
	}
	return TRUE;
}


BOOL GStackWalker::GetSymAndInitSym()
{
	if (m_modulesLoaded != FALSE)
		return TRUE;

	// 建立符号路径
	CHAR* szSymPath = (char*)malloc(SYMBOL_PATH_LEN);
	if (szSymPath == NULL)
	{
		SetLastError(ERROR_NOT_ENOUGH_MEMORY);
		return FALSE;
	}

	szSymPath[0] = 0;

	// 首先将用户提供的符号路径添加进来
	if (m_szSymPath != NULL)
	{
		GStrCat(szSymPath, SYMBOL_PATH_LEN, m_szSymPath);
		GStrCat(szSymPath, SYMBOL_PATH_LEN, ";");// 路径之间用";" 加以分割
	}

	GStrCat(szSymPath, SYMBOL_PATH_LEN, ";");

	const size_t nTempLen = 1024;
	char szTemp[nTempLen];
	// 得到当前路径
	if (GetCurrentDirectoryA(nTempLen, szTemp) > 0)
	{
		szTemp[nTempLen - 1] = 0;
		GStrCat(szSymPath, SYMBOL_PATH_LEN, szTemp);
		GStrCat(szSymPath, SYMBOL_PATH_LEN, ";");
	}

	// 得到主模块的路径
	if (GetModuleFileNameA(NULL, szTemp, nTempLen) > 0)
	{
		szTemp[nTempLen - 1] = 0;
 		for (char* p = (szTemp + GStrLen(szTemp) - 1); p >= szTemp; --p)
		{
			// 得到最右路径
			if ((*p == '\\') || (*p == '/') || (*p == ':'))
			{
				*p = 0;
				break;
			}
		}  // for (search for path separator...)
		if (GStrLen(szTemp) > 0)
		{
			GStrCat(szSymPath, SYMBOL_PATH_LEN, szTemp);
			GStrCat(szSymPath, SYMBOL_PATH_LEN, ";");
		}
	}
	// 得到环境变量路径 系统符号路径
	if (GetEnvironmentVariableA("_NT_SYMBOL_PATH", szTemp, nTempLen) > 0)
	{
		szTemp[nTempLen - 1] = 0;
		GStrCat(szSymPath, SYMBOL_PATH_LEN, szTemp);
		GStrCat(szSymPath, SYMBOL_PATH_LEN, ";");
	}
	// 得到 NT 交替符号路径
	if (GetEnvironmentVariableA("_NT_ALTERNATE_SYMBOL_PATH", szTemp, nTempLen) > 0)
	{
		szTemp[nTempLen - 1] = 0;
		GStrCat(szSymPath, SYMBOL_PATH_LEN, szTemp);
		GStrCat(szSymPath, SYMBOL_PATH_LEN, ";");
	}
	// 得到系统根路径 及其 \\system32 子路径
	if (GetEnvironmentVariableA("SYSTEMROOT", szTemp, nTempLen) > 0)
	{
		szTemp[nTempLen - 1] = 0;
		GStrCat(szSymPath, SYMBOL_PATH_LEN, szTemp);
		GStrCat(szSymPath, SYMBOL_PATH_LEN, ";");
		// also add the "system32"-directory:
		GStrCat(szTemp, nTempLen, "\\system32");
		GStrCat(szSymPath, SYMBOL_PATH_LEN, szTemp);
		GStrCat(szSymPath, SYMBOL_PATH_LEN, ";");
	}

	// 得到 系统驱动 环境变量
	if (GetEnvironmentVariableA("SYSTEMDRIVE", szTemp, nTempLen) > 0)
	{
		szTemp[nTempLen - 1] = 0;
		GStrCat(szSymPath, SYMBOL_PATH_LEN, "SRV*");
		GStrCat(szSymPath, SYMBOL_PATH_LEN, szTemp);
		GStrCat(szSymPath, SYMBOL_PATH_LEN, "\\websymbols");
		GStrCat(szSymPath, SYMBOL_PATH_LEN, "*http://msdl.microsoft.com/download/symbols;");
	}
	else	// 最后加入微软的官方在线符号表
		GStrCat(szSymPath, SYMBOL_PATH_LEN, "SRV*c:\\websymbols*http://msdl.microsoft.com/download/symbols;");

	if (!InitSym(szSymPath))
	{
		return FALSE;
	}

	if (szSymPath != NULL) free(szSymPath); szSymPath = NULL;
	return TRUE;
}

DWORD GStackWalker::LoadModule(HANDLE hProcess, LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size)
{
	CHAR* szImg = _strdup(img);
	CHAR* szMod = _strdup(mod);
	DWORD result = ERROR_SUCCESS;

	if ((szImg == NULL) || (szMod == NULL))
		result = ERROR_NOT_ENOUGH_MEMORY;
	else
	{
		if (SymLoadModule64(hProcess, 0, szImg, szMod, baseAddr, size) == 0)
			result = GetLastError();
	}

	if (szImg != NULL) free(szImg);
	if (szMod != NULL) free(szMod);
	szImg = NULL;
	szMod = NULL;

	return result;
}

/**
 * 枚举进程模块并为每个模块加载符号
 */
BOOL GStackWalker::LoadModules()
{
	DWORD Threads[50];
	int i = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_dwProcessId);
	if (hSnap == INVALID_HANDLE_VALUE)
		return FALSE;

	MODULEENTRY32 me;
	me.dwSize = sizeof(me);
	if (Module32First(hSnap, &me) == FALSE)
	{
		CloseHandle(hSnap);
		return FALSE;
	}

	do{
		LoadModule(m_hProcess, (LPCSTR)me.szExePath, (LPCSTR)me.szModule, (DWORD64)me.modBaseAddr, me.modBaseSize);
	} while (Module32Next(hSnap, &me) != FALSE);

	m_modulesLoaded = TRUE;
	return TRUE;
}

BOOL GStackWalker::IsInitialized()
{
	return m_bInitalizeSuc;
}

BOOL GStackWalker::ShowCallStack(HANDLE hProcess, DWORD dwThreadId)
{
	IMAGEHLP_SYMBOL64* pSym = NULL;
	int frameNum;

	if (m_modulesLoaded == FALSE)
		LoadModules();

	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, dwThreadId);

	CONTEXT c;
	memset(&c, 0, sizeof(c));
	GET_CURRENT_CONTEXT(c, USED_CONTEXT_FLAGS)

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

	pSym = (IMAGEHLP_SYMBOL64*)malloc(sizeof(IMAGEHLP_SYMBOL64) + STACKWALK_MAX_NAMELEN);
	if (!pSym) 
		goto cleanup;

	memset(pSym, 0, sizeof(IMAGEHLP_SYMBOL64) + STACKWALK_MAX_NAMELEN);
	pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
	pSym->MaxNameLength = STACKWALK_MAX_NAMELEN;
	IMAGEHLP_MODULE64 Module;
	memset(&Module, 0, sizeof(Module));
	Module.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);

	for (frameNum = 0;; frameNum++)
	{
		// 取下一个栈帧(StackWalk64(), SymFunctionTableAccess64(), SymGetModuleBase64())
		//函数的三个回调函数可以传入自己的回调函数，也可以传入DbgHelp.dll 自己的函数

		if (!StackWalk64(imageType, m_hProcess, hThread, &s, &c, MyReadProcMem, SymFunctionTableAccess64, SymGetModuleBase64, NULL))
			break;

		CallstackEntry csEntry;
		csEntry.offset = s.AddrPC.Offset;// 这里的AddrPC（程序计数器） 就是EIP/RIP，即调用位置
		csEntry.FuncName[0] = 0;
		csEntry.offsetFromSmybol = 0;
		csEntry.loadedImageName[0] = 0;
		csEntry.moduleName[0] = 0;
		if (s.AddrPC.Offset != 0)
		{
			//得到了合法的IP
			// 显示程序符号信息(SymGetSymFromAddr64())
			if (SymGetSymFromAddr64(this->m_hProcess, s.AddrPC.Offset, &(csEntry.offsetFromSmybol), pSym) != FALSE)
				strcpy_s(csEntry.FuncName, pSym->Name);

			// 得到模块信息 (SymGetModuleInfo64())
			if (SymGetModuleInfo64(this->m_hProcess, s.AddrPC.Offset, &Module) != FALSE)
			{
				strcpy_s(csEntry.moduleName, Module.ModuleName);
				csEntry.baseOfImage = Module.BaseOfImage;
				strcpy_s(csEntry.loadedImageName, Module.LoadedImageName);
			}

			IMAGEHLP_LINE lineInfo = { sizeof(IMAGEHLP_LINE) };
			DWORD dwLineDisplacement;
			if (SymGetLineFromAddr64(hProcess, s.AddrPC.Offset, &dwLineDisplacement, &lineInfo))
			{
				csEntry.Lines = lineInfo;
				printf("%u", dwLineDisplacement);
			}
			else
			{

			}

			ShowMessage(csEntry);

			if (s.AddrReturn.Offset == 0)
				break;
		}
	}

cleanup:
	if (pSym) free(pSym);

	if (hThread != NULL && hThread != INVALID_HANDLE_VALUE)
		ResumeThread(hThread);
	return TRUE;
}

void GStackWalker::ShowMessage(CallstackEntry entry)
{
	if (entry.FuncName[0] != NULL)
	{
#ifndef _M_X64
		printf("call address: %8p  ", entry.offset - 5);
		printf("%s", entry.moduleName);
		printf("!%s", entry.FuncName);
		printf("+0x%8p\r\n", entry.offsetFromSmybol);
#else
		GOutputDebugString(TEXT("call address：%p  %s!%s+0x%x  filename:%s  lines:%d \r\n"), entry.offset - 5, GPConstChar_To_PTCHAR(entry.moduleName), GPConstChar_To_PTCHAR(entry.FuncName), entry.offsetFromSmybol, GPConstChar_To_PTCHAR(entry.Lines.FileName), entry.Lines.LineNumber);
		printf("call address：%p  %s!%s+0x%x  filename:%s  lines:%d \r\n", entry.offset - 5, entry.moduleName, entry.FuncName, entry.offsetFromSmybol,entry.Lines.FileName,entry.Lines.LineNumber);
#endif
	}
	else
	{
#ifndef _M_X64
		printf("call address：%8p\t%s+0x%8p\r\n", entry.offset - 5, entry.moduleName, entry.offset - entry.baseOfImage);
#else // !_M_X64
		printf("call address：%16p\t%s+0x%x\t filename:%s line:%u\r\n", entry.offset - 5, entry.moduleName, entry.offset - entry.baseOfImage,entry.Lines.FileName,entry.Lines.LineNumber);
#endif
	}
}

void GStackWalker::GetStackFrameEntryAddressArray(HANDLE hProcess, DWORD dwThreadId, DWORD64 frames[STACK_MAX_RECORD])
{
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, dwThreadId);
	GASSERT(hProcess != NULL);
	GASSERT(hThread != NULL);

	int frameNum;
	CONTEXT c;
	memset(&c, 0, sizeof(c));
	GET_CURRENT_CONTEXT(c, USED_CONTEXT_FLAGS)

	STACKFRAME64 sf64;
	memset(&sf64, 0, sizeof(sf64));

	DWORD ImageType;
	//根据平台定义栈帧参数
#ifdef _M_IX86
	ImageType = IMAGE_FILE_MACHINE_I386;
	sf64.AddrPC.Offset = c.Eip;
	sf64.AddrPC.Mode = AddrModeFlat;
	sf64.AddrFrame.Offset = c.Ebp;
	sf64.AddrFrame.Mode = AddrModeFlat;
	sf64.AddrStack.Offset = c.Esp;
	sf64.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
	ImageType = IMAGE_FILE_MACHINE_AMD64;
	sf64.AddrPC.Offset = c.Rip;
	sf64.AddrPC.Mode = AddrModeFlat;
	sf64.AddrFrame.Offset = c.Rsp;
	sf64.AddrFrame.Mode = AddrModeFlat;
	sf64.AddrStack.Offset = c.Rsp;
	sf64.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
	ImageType = IMAGE_FILE_MACHINE_IA64;
	sf64.AddrPC.Offset = c.StIIP;
	sf64.AddrPC.Mode = AddrModeFlat;
	sf64.AddrFrame.Offset = c.IntSp;
	sf64.AddrFrame.Mode = AddrModeFlat;
	sf64.AddrBStore.Offset = c.RsBSP;
	sf64.AddrBStore.Mode = AddrModeFlat;
	sf64.AddrStack.Offset = c.IntSp;
	sf64.AddrStack.Mode = AddrModeFlat;
#else
#error "Platform not supported!"
#endif

	IMAGEHLP_MODULE64 Module;
	memset(&Module, 0, sizeof(Module));
	Module.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);

	for (frameNum = 0; frameNum < STACK_MAX_RECORD; frameNum++)
	{
		// 取下一个栈帧(StackWalk64(), SymFunctionTableAccess64(), SymGetModuleBase64())
		//函数的三个回调函数可以传入自己的回调函数，也可以传入自己的函数    DbgHelp.dll 
		if (!StackWalk64(ImageType, hProcess, hThread, &sf64, &c, MyReadProcMem, SymFunctionTableAccess64, SymGetModuleBase64, NULL))
			break;

		if (sf64.AddrPC.Offset != 0)
			frames[frameNum] = sf64.AddrPC.Offset;

		if (sf64.AddrReturn.Offset == 0)
			break;
	}

	if (hThread != NULL && hThread != INVALID_HANDLE_VALUE)
		ResumeThread(hThread);
}

void GStackWalker::PrintCallStackFramesLog(DWORD64 frames[STACK_MAX_RECORD], HANDLE hProcess)
{
	GASSERT(frames != NULL);

	if (hProcess == NULL)
		hProcess = GetCurrentProcess();

	IMAGEHLP_SYMBOL64* pSym = NULL;
	pSym = (IMAGEHLP_SYMBOL64*)malloc(sizeof(IMAGEHLP_SYMBOL64) + STACKWALK_MAX_NAMELEN);
	if (!pSym)
	{
		GOutputDebugString(TEXT("Memory Overflow..."));
		return;
	}

	memset(pSym, 0, sizeof(IMAGEHLP_SYMBOL64) + STACKWALK_MAX_NAMELEN);
	pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
	pSym->MaxNameLength = STACKWALK_MAX_NAMELEN;
	IMAGEHLP_MODULE64 Module;
	memset(&Module, 0, sizeof(Module));
	Module.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);

	size_t frameNum = 0;
	while (frames[frameNum] != 0)
	{
		CallstackEntry csEntry;
		csEntry.offset = frames[frameNum];
		csEntry.FuncName[0] = 0;
		csEntry.offsetFromSmybol = 0;
		csEntry.loadedImageName[0] = 0;
		csEntry.moduleName[0] = 0;

		if (frames[frameNum] != 0)
		{
			//得到了合法的IP
			// 显示程序符号信息(SymGetSymFromAddr64())
			if (SymGetSymFromAddr64(this->m_hProcess, frames[frameNum], &(csEntry.offsetFromSmybol), pSym) != FALSE)
				strcpy_s(csEntry.FuncName, pSym->Name);

			// 得到模块信息 (SymGetModuleInfo64())
			if (SymGetModuleInfo64(this->m_hProcess, frames[frameNum], &Module) != FALSE)
			{
				strcpy_s(csEntry.moduleName, Module.ModuleName);
				csEntry.baseOfImage = Module.BaseOfImage;
				strcpy_s(csEntry.loadedImageName, Module.LoadedImageName);
			}

			IMAGEHLP_LINE lineInfo = { sizeof(IMAGEHLP_LINE) };
			DWORD dwLineDisplacement;
			if (SymGetLineFromAddr64(hProcess, frames[frameNum], &dwLineDisplacement, &lineInfo))
			{
				csEntry.Lines = lineInfo;
			}

			ShowMessage(csEntry);
			frameNum++;
		}
		else
			break;
	}

	if (pSym)
		free(pSym);
}