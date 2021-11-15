#ifndef GSYSTEM_H
#define GSYSTEM_H

#include <assert.h>  
#include <Windows.h>
#include <DbgHelp.h>
#include <stdarg.h>
#include <tchar.h>

#define GSYSTEM_EXPORTS
#ifdef GSYSTEM_EXPORTS
#define GSYSTEM_API __declspec(dllexport) 
#else 
#define GSYSTEM_API __declspec(dllimport) 
#endif

namespace GEngine
{
#define GASSERT(x)  assert(x)

	namespace GSystem
	{
		FORCEINLINE VOID GOutputDebugString(const TCHAR* pcString, ...)
		{
			char* pArgs = (char*)&pcString + sizeof(pcString);
			TCHAR ms_logBuffer[65536];
			_vstprintf_s(ms_logBuffer, 65536, pcString, pArgs);
			OutputDebugString(ms_logBuffer);
		}

		FORCEINLINE TCHAR* GPConstChar_To_PTCHAR(const char* Str)
		{
			size_t size = MultiByteToWideChar(CP_ACP, 0, Str, -1, NULL, 0);
			ULONGLONG len = sizeof(TCHAR) * size;
			TCHAR* str = new TCHAR[len];
			MultiByteToWideChar(CP_ACP, 0, (LPCCH)Str, -1, (LPWSTR)str, len);
			return str;
		}
	}
}


#endif // !GSYSTEM_H
