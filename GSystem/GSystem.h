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

		//�ַ�����������
        //**********************************************************************************************************************************************

		/// <summary>
		/// ����TCHAR�����ַ����鳤�ȣ��������ַ���������NULL��
		/// </summary>
		/// <param name="str">Ŀ���ַ�����</param>
		/// <returns>�ַ�������</returns>
		FORCEINLINE size_t GStrLen(const TCHAR* str)
		{
            #ifdef WINDOWS
			    return _tcslen(str);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// ����CHAR�����ַ����鳤�ȣ��������ַ���������NULL��
		/// </summary>
		/// <param name="str">Ŀ���ַ�����</param>
		/// <returns>�ַ�������</returns>
		FORCEINLINE size_t GStrLen(const CHAR* str)
		{
            #ifdef WINDOWS
			    return strlen(str);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// ����char16_t�����ַ����顾�Ĵ������������ȣ��������ַ���������NULL��
		/// </summary>
		/// <param name="str">Ŀ���ַ�����</param>
		/// <returns>�ַ�������</returns>
		FORCEINLINE size_t GStrLen(register const char16_t* str)
		{
			if (!str)
				return 0;
			register size_t len = 0;
			while (str[len++]);
			return len - 1;
		}

		/// <summary>
		/// ����char32_t�����ַ����顾�Ĵ������������ȣ��������ַ���������NULL��
		/// </summary>
		/// <param name="str">Ŀ���ַ�����</param>
		/// <returns>�ַ�������</returns>
		FORCEINLINE size_t GStrLen(register const char32_t* str)
		{
			if (!str)
				return 0;
			register size_t len = 0;
			while (str[len++]);
			return len - 1;
		}


		/// <summary>
		/// �ַ�����ĸ���
		/// </summary>
		/// <param name="dest">����ַ�����</param>
		/// <param name="destlen">�������������</param>
		/// <param name="source">Դ�ַ�����</param>
		/// <returns>ʵ�ʸ��Ƶĳ���</returns>
		FORCEINLINE errno_t GStrCpy(TCHAR* dest, size_t destlen, const TCHAR* source)
		{
            #ifdef WINDOWS
			    return _tcscpy_s(dest, destlen, source);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// �ַ�����ĸ���
		/// </summary>
		/// <param name="dest">����ַ�����</param>
		/// <param name="destlen">�������������</param>
		/// <param name="source">Դ�ַ�����</param>
		/// <returns>ʵ�ʸ��Ƶĳ���</returns>
		FORCEINLINE errno_t GStrCpy(CHAR* dest, size_t destlen, const CHAR* source)
		{
#ifdef WINDOWS
			return strcpy_s(dest, destlen, source);
#else
			return NULL;
#endif
		}

		/// <summary>
		/// �ַ�����ĸ���
		/// </summary>
		/// <param name="dest">����ַ�����</param>
		/// <param name="destlen">�������������</param>
		/// <param name="source">Դ�ַ�����</param>
		/// <param name="cmplen">���Ƶĳ���</param>
		/// <returns>ʵ�ʸ��Ƶĳ���</returns>
		FORCEINLINE errno_t GStrCpy(TCHAR* dest, unsigned int destlen, const TCHAR* source, unsigned int cmplen)
		{
            #ifdef WINDOWS
			    return _tcsncpy_s(dest, destlen, source, cmplen);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// ��ָ��TCHAR�ַ����ӵ�ĳһ�ַ�����ĩβ
		/// </summary>
		/// <param name="dest">����ַ�����</param>
		/// <param name="destlen">�������������</param>
		/// <param name="endStr">����ĩβ���ַ�����</param>
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
		/// ��ָ��TCHAR�ַ����ӵ�ĳһ�ַ�����ĩβ
		/// </summary>
		/// <param name="dest">����ַ�����</param>
		/// <param name="destlen">�������������</param>
		/// <param name="endStr">Դ�ַ�����</param>
		/// <param name="catlen">���ĳ���</param>
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
		/// ��ָ��TCHAR�ַ����ӵ�ĳһ�ַ�����ĩβ
		/// </summary>
		/// <param name="dest">����ַ�����</param>
		/// <param name="destlen">�������������</param>
		/// <param name="endStr">Դ�ַ�����</param>
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
		/// �Ƚ��ַ���
		/// </summary>
		/// <param name="str1">�ַ���1</param>
		/// <param name="str2">�ַ���2</param>
		/// <returns>���ݱȽϽ�����ظ��� �� 0 �� ����</returns>
		FORCEINLINE int GStrCmp(TCHAR* str1, TCHAR* str2)
		{
            #ifdef WINDOWS
			    return _tcscmp(str1, str2);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// �Ƚ��ַ���
		/// </summary>
		/// <param name="str1">�ַ���1</param>
		/// <param name="str2">�ַ���2</param>
		/// <param name="cmplen">�Ƚϵĳ���</param>
		/// <returns>���ݱȽϽ�����ظ��� �� 0 �� ����</returns>
		FORCEINLINE int GStrCmp(TCHAR* str1, TCHAR* str2, size_t cmplen)
		{
            #ifdef WINDOWS
			    return _tcsncmp(str1, str2, cmplen);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// ���ַ�����
		/// </summary>
		/// <param name="opStr">����Ŀ��</param>
		/// <param name="c">��Ҫ���ҵ��ַ�</param>
		/// <returns>����һ��ָ���ַ����е�һ�γ��ֵĸ��ַ���ָ��</returns>
		FORCEINLINE TCHAR* GStrChr(TCHAR* opStr, TCHAR c)
		{
            #ifdef WINDOWS
			    return _tcsrchr(opStr, c);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// ��strToken�ַ����У������ṩ�ķָ���strDelimit����ȡ�������ַ������飻
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
		/// char�ַ���תΪTCHAR�ַ���(ע��Ҫ�ͷŷ����ַ������ڴ�)
		/// </summary>
		/// <param name="Str">char�ַ���</param>
		/// <returns>TCHAR�ַ���</returns>
		FORCEINLINE void GPConstChar_To_PTCHAR(const char* source, TCHAR* dest, int destMaxLen)
		{
			size_t size = MultiByteToWideChar(CP_ACP, 0, source, -1, NULL, 0);
			size = size > destMaxLen ? destMaxLen : size;
			ULONGLONG len = sizeof(TCHAR) * size;
			MultiByteToWideChar(CP_ACP, 0, (LPCCH)source, -1, (LPWSTR)dest, len);
			dest[size + 1] = '\0';
		}

		/// <summary>
		/// TCHAR�ַ���תΪchar�ַ���
		/// </summary>
		/// <param name="Str">TCHAR�ַ���</param>
		/// <returns>char�����ַ���</returns>
		FORCEINLINE void GPTCHAR_To_PConstChar(const TCHAR* source, CHAR* dest, int destMaxLen)
		{
			size_t size = WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)source, -1, NULL, 0, NULL, FALSE);
			size = size > destMaxLen ? destMaxLen : size;
			WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)source, -1, (LPSTR)dest, size, NULL, FALSE);
		}

		/// <summary>
		/// ��Output����̨��ʽ��ӡĳ��TCHAR�ַ���
		/// </summary>
		/// <param name="pcString">��ӡ��ʽ</param>
		/// <param name="...">��ʽ�е���ֵ(�ɱ����)</param>
		FORCEINLINE VOID GOutputDebugStringW(const TCHAR* pcString, ...)
		{
			char* pArgs = (char*)&pcString + sizeof(pcString);
			_vstprintf_s(GSystem::GetLogBufferW(), GSYSTEM_LOG_BUFFER_SIZE, pcString, pArgs);
			OutputDebugString(GSystem::GetLogBufferW());
		}

		/// <summary>
		/// ��Output����̨��ʽ��ӡĳ��CHAR�ַ���
		/// </summary>
		/// <param name="pcString">��ӡ��ʽ</param>
		/// <param name="...">��ʽ�е���ֵ(�ɱ����)</param>
		FORCEINLINE VOID GOutputDebugStringA(const CHAR* pcString, ...)
		{
			char* pArgs = (char*)&pcString + sizeof(pcString);
			vsnprintf(GSystem::GetLogBufferA(), GSYSTEM_LOG_BUFFER_SIZE, pcString, pArgs);
			OutputDebugStringA(GSystem::GetLogBufferA());
		}


		//�ڴ��������
		//**********************************************************************************************************************************************

		/// <summary>
		/// �ڴ渴��
		/// </summary>
		/// <param name="dest">�������</param>
		/// <param name="destlen">����������ĳ���</param>
		/// <param name="source">����Ŀ��</param>
		/// <param name="sourcelen">����Ŀ�껺�����ĳ���</param>
		/// <returns>���ƽ����int���ͣ�</returns>
		FORCEINLINE errno_t GMemoryCpy(void* dest, size_t destlen, void* source, size_t sourcelen)
		{
            #ifdef WINDOWS
			    return memcpy_s(dest, destlen, source, sourcelen);
            #else
			    return NULL;
            #endif
		}


		/// <summary>
		/// �����ڴ�
		/// @notes:
		/// ���ڴ淢���ֲ��ص���ʱ��memmove��֤�����Ľ������ȷ�ģ�memcpy����֤�����Ľ������ȷ
		/// memcopy��memmove���ٶ�Ҫ��һЩ
		/// </summary>
		/// <param name="dest">�������</param>
		/// <param name="destlen">����������ĳ���</param>
		/// <param name="source">����Ŀ��</param>
		/// <param name="sourcelen">����Ŀ�껺�����ĳ���</param>
		/// <returns>���ƽ����int���ͣ�</returns>
		FORCEINLINE errno_t GMemoryMove(void* dest, size_t destlen, void* source, size_t sourcelen)
		{
            #ifdef WINDOWS
			    return memmove_s(dest, destlen, source, sourcelen);
            #else
			    return NULL;
            #endif
		}

		/// <summary>
		/// �Ƚ��ڴ�
		/// </summary>
		/// <param name="dest">�ڴ����ʼ��ַ1</param>
		/// <param name="source">�ڴ����ʼ��ַ2</param>
		/// <param name="cmplen">�Ƚϵĳ���</param>
		/// <returns>�ȽϽ����int���ͣ�</returns>
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
