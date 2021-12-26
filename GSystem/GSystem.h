#ifndef GSYSTEM_H
#define GSYSTEM_H

#include <assert.h>  
#include <Windows.h>
#include <DbgHelp.h>
#include <stdarg.h>
#include <tchar.h>
#include <stdio.h>

#pragma comment(lib, "winmm.lib ")
#pragma comment(lib,"Shlwapi.lib")

#define GSYSTEM_EXPORTS
#ifdef GSYSTEM_EXPORTS
#define GSYSTEM_API __declspec(dllexport) 
#else 
#define GSYSTEM_API __declspec(dllimport) 
#endif

#define GASSERT(x)  assert(x)
#define GNEW        new
#define GDELETE     delete

#define GSAFE_DELETE(x) if (x != nullptr)\
{\
    GDELETE x;\
	x = nullptr;\
}\

#define GSAFE_DELETE_ARRAY(x) if (x != nullptr)\
{\
	GDELETE[] x;\
	x = nullptr;\
}\

namespace GEngine
{
	namespace GSystem
	{
        #define GSYSTEM_LOG_BUFFER_SIZE 65536

		class GSYSTEM_API GSystem
		{
		private:
			static TCHAR ms_logBufferW[GSYSTEM_LOG_BUFFER_SIZE];
			static CHAR ms_logBufferA[GSYSTEM_LOG_BUFFER_SIZE];
			static DWORD ms_dwMainThreadID;

		public:
			static TCHAR* GetLogBufferW();
			static CHAR* GetLogBufferA();
			static DWORD GetMainThreadID();
		};

#define WINDOWS

		//字符串操作函数
        //**********************************************************************************************************************************************

		/// <summary>
		/// 返回TCHAR类型字符数组长度（不包括字符串结束符NULL）
		/// </summary>
		/// <param name="str">目标字符数组</param>
		/// <returns>字符串长度</returns>
		FORCEINLINE size_t GStrLen(const TCHAR* str)
		{
            #ifdef WINDOWS
			    return _tcslen(str);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// 返回CHAR类型字符数组长度（不包括字符串结束符NULL）
		/// </summary>
		/// <param name="str">目标字符数组</param>
		/// <returns>字符串长度</returns>
		FORCEINLINE size_t GStrLen(const CHAR* str)
		{
            #ifdef WINDOWS
			    return strlen(str);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// 返回char16_t类型字符数组【寄存器变量】长度（不包括字符串结束符NULL）
		/// </summary>
		/// <param name="str">目标字符数组</param>
		/// <returns>字符串长度</returns>
		FORCEINLINE size_t GStrLen(register const char16_t* str)
		{
			if (!str)
				return 0;
			register size_t len = 0;
			while (str[len++]);
			return len - 1;
		}

		/// <summary>
		/// 返回char32_t类型字符数组【寄存器变量】长度（不包括字符串结束符NULL）
		/// </summary>
		/// <param name="str">目标字符数组</param>
		/// <returns>字符串长度</returns>
		FORCEINLINE size_t GStrLen(register const char32_t* str)
		{
			if (!str)
				return 0;
			register size_t len = 0;
			while (str[len++]);
			return len - 1;
		}


		/// <summary>
		/// 字符数组的复制
		/// </summary>
		/// <param name="dest">结果字符数组</param>
		/// <param name="destlen">结果缓冲区长度</param>
		/// <param name="source">源字符数组</param>
		/// <returns>实际复制的长度</returns>
		FORCEINLINE errno_t GStrCpy(TCHAR* dest, size_t destlen, const TCHAR* source)
		{
            #ifdef WINDOWS
			    return _tcscpy_s(dest, destlen, source);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// 字符数组的复制
		/// </summary>
		/// <param name="dest">结果字符数组</param>
		/// <param name="destlen">结果缓冲区长度</param>
		/// <param name="source">源字符数组</param>
		/// <returns>实际复制的长度</returns>
		FORCEINLINE errno_t GStrCpy(CHAR* dest, size_t destlen, const CHAR* source)
		{
#ifdef WINDOWS
			return strcpy_s(dest, destlen, source);
#else
			return NULL;
#endif
		}

		/// <summary>
		/// 字符数组的复制
		/// </summary>
		/// <param name="dest">结果字符数组</param>
		/// <param name="destlen">结果缓冲区长度</param>
		/// <param name="source">源字符数组</param>
		/// <param name="cmplen">复制的长度</param>
		/// <returns>实际复制的长度</returns>
		FORCEINLINE errno_t GStrCpy(TCHAR* dest, unsigned int destlen, const TCHAR* source, unsigned int cmplen)
		{
            #ifdef WINDOWS
			    return _tcsncpy_s(dest, destlen, source, cmplen);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// 将指定TCHAR字符串接到某一字符串的末尾
		/// </summary>
		/// <param name="dest">结果字符数组</param>
		/// <param name="destlen">结果缓冲区长度</param>
		/// <param name="endStr">接于末尾的字符数组</param>
		/// <returns></returns>
		FORCEINLINE errno_t GStrCat(TCHAR* dest, size_t destlen, const TCHAR* endStr)
		{
            #ifdef WINDOWS
			    return _tcscat_s(dest, destlen, endStr);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// 将指定TCHAR字符串接到某一字符串的末尾
		/// </summary>
		/// <param name="dest">结果字符数组</param>
		/// <param name="destlen">结果缓冲区长度</param>
		/// <param name="endStr">源字符数组</param>
		/// <param name="catlen">最大的长度</param>
		/// <returns></returns>
		FORCEINLINE errno_t GStrCat(TCHAR* dest, size_t destlen, const TCHAR* endStr, int catlen)
		{
            #ifdef WINDOWS
			    return _tcsncat_s(dest, destlen, endStr, catlen);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// 将指定TCHAR字符串接到某一字符串的末尾
		/// </summary>
		/// <param name="dest">结果字符数组</param>
		/// <param name="destlen">结果缓冲区长度</param>
		/// <param name="endStr">源字符数组</param>
		/// <returns></returns>
		CFORCEINLINE errno_t GStrCat(CHAR* dest, size_t destlen, const CHAR* endStr)
		{
			#ifdef WINDOWS
				return strcat_s(dest,destlen,endStr);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// 比较字符串
		/// </summary>
		/// <param name="str1">字符串1</param>
		/// <param name="str2">字符串2</param>
		/// <returns>根据比较结果返回负数 ， 0 ， 正数</returns>
		FORCEINLINE int GStrCmp(TCHAR* str1, TCHAR* str2)
		{
            #ifdef WINDOWS
			    return _tcscmp(str1, str2);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// 比较字符串
		/// </summary>
		/// <param name="str1">字符串1</param>
		/// <param name="str2">字符串2</param>
		/// <param name="cmplen">比较的长度</param>
		/// <returns>根据比较结果返回负数 ， 0 ， 正数</returns>
		FORCEINLINE int GStrCmp(TCHAR* str1, TCHAR* str2, size_t cmplen)
		{
            #ifdef WINDOWS
			    return _tcsncmp(str1, str2, cmplen);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// 子字符查找
		/// </summary>
		/// <param name="opStr">查找目标</param>
		/// <param name="c">想要查找的字符</param>
		/// <returns>返回一个指向字符串中第一次出现的该字符的指针</returns>
		FORCEINLINE TCHAR* GStrChr(TCHAR* opStr, TCHAR c)
		{
            #ifdef WINDOWS
			    return _tcsrchr(opStr, c);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// 从strToken字符串中，根据提供的分隔符strDelimit，截取并返回字符串数组；
		/// </summary>
		/// <param name="strToken"></param>
		/// <param name="strDelimit"></param>
		/// <param name="pContext"></param>
		/// <returns></returns>
		FORCEINLINE TCHAR* GStrtok(TCHAR* strToken, const TCHAR* strDelimit, TCHAR** pContext)
		{
            #ifdef WINDOWS
			    return _tcstok_s(strToken, strDelimit, pContext);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// char字符串转为TCHAR字符串(注意要释放返回字符串的内存)
		/// </summary>
		/// <param name="Str">char字符串</param>
		/// <returns>TCHAR字符串</returns>
		FORCEINLINE void GPConstChar_To_PTCHAR(const char* source, TCHAR* dest, int destMaxLen)
		{
			size_t size = MultiByteToWideChar(CP_ACP, 0, source, -1, NULL, 0);
			size = size > destMaxLen ? destMaxLen : size;
			ULONGLONG len = sizeof(TCHAR) * size;
			MultiByteToWideChar(CP_ACP, 0, (LPCCH)source, -1, (LPWSTR)dest, len);
			dest[size + 1] = '\0';
		}

		/// <summary>
		/// TCHAR字符串转为char字符串
		/// </summary>
		/// <param name="Str">TCHAR字符串</param>
		/// <returns>char类型字符串</returns>
		FORCEINLINE void GPTCHAR_To_PConstChar(const TCHAR* source, CHAR* dest, int destMaxLen)
		{
			size_t size = WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)source, -1, NULL, 0, NULL, FALSE);
			size = size > destMaxLen ? destMaxLen : size;
			WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)source, -1, (LPSTR)dest, size, NULL, FALSE);
		}

		/// <summary>
		/// 向Output控制台格式打印某个TCHAR字符串
		/// </summary>
		/// <param name="pcString">打印格式</param>
		/// <param name="...">格式中的数值(可变参数)</param>
		FORCEINLINE VOID GOutputDebugStringW(const TCHAR* pcString, ...)
		{
			char* pArgs = (char*)&pcString + sizeof(pcString);
			_vstprintf_s(GSystem::GetLogBufferW(), GSYSTEM_LOG_BUFFER_SIZE, pcString, pArgs);
			OutputDebugString(GSystem::GetLogBufferW());
		}

		/// <summary>
		/// 向Output控制台格式打印某个CHAR字符串
		/// </summary>
		/// <param name="pcString">打印格式</param>
		/// <param name="...">格式中的数值(可变参数)</param>
		FORCEINLINE VOID GOutputDebugStringA(const CHAR* pcString, ...)
		{
			char* pArgs = (char*)&pcString + sizeof(pcString);
			vsnprintf(GSystem::GetLogBufferA(), GSYSTEM_LOG_BUFFER_SIZE, pcString, pArgs);
			OutputDebugStringA(GSystem::GetLogBufferA());
		}


		//内存操作函数
		//**********************************************************************************************************************************************

		/// <summary>
		/// 内存复制
		/// </summary>
		/// <param name="dest">拷贝结果</param>
		/// <param name="destlen">结果缓冲区的长度</param>
		/// <param name="source">复制目标</param>
		/// <param name="sourcelen">复制目标缓冲区的长度</param>
		/// <returns>复制结果（int类型）</returns>
		FORCEINLINE errno_t GMemoryCpy(void* dest, size_t destlen, void* source, size_t sourcelen)
		{
            #ifdef WINDOWS
			    return memcpy_s(dest, destlen, source, sourcelen);
            #else
			    return NULL;
            #endif
		}


		/// <summary>
		/// 复制内存
		/// @notes:
		/// 当内存发生局部重叠的时候，memmove保证拷贝的结果是正确的，memcpy不保证拷贝的结果的正确
		/// memcopy比memmove的速度要快一些
		/// </summary>
		/// <param name="dest">拷贝结果</param>
		/// <param name="destlen">结果缓冲区的长度</param>
		/// <param name="source">复制目标</param>
		/// <param name="sourcelen">复制目标缓冲区的长度</param>
		/// <returns>复制结果（int类型）</returns>
		FORCEINLINE errno_t GMemoryMove(void* dest, size_t destlen, void* source, size_t sourcelen)
		{
            #ifdef WINDOWS
			    return memmove_s(dest, destlen, source, sourcelen);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// 比较内存
		/// </summary>
		/// <param name="dest">内存块起始地址1</param>
		/// <param name="source">内存块起始地址2</param>
		/// <param name="cmplen">比较的长度</param>
		/// <returns>比较结果（int类型）</returns>
		FORCEINLINE int GMemoryCmp(void* dest, void* source, size_t cmplen)
		{
            #ifdef WINDOWS
			    return memcmp(dest, source, cmplen);
            #else
			    return NULL;
            #endif
		}



		FORCEINLINE void GLockedIncrement(long* pRefCount)
		{
            #ifdef WINDOWS
			    _InterlockedIncrement(pRefCount);
            #else
			    return;
            #endif
		}
		FORCEINLINE void GLockedDecrement(long* pRefCount)
		{
            #ifdef WINDOWS
            	_InterlockedDecrement(pRefCount);
            #else
            	return;
            #endif
		}
	}
}


#endif // !GSYSTEM_H
