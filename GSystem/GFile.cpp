#include "GFile.h"
#include <Shlwapi.h>
using namespace GEngine::GSystem;

GFile::GFile()
{
	m_pcFileName = GNEW CHAR[MAX_PATH_LENGTH];
	m_ptFileName = GNEW TCHAR[MAX_PATH_LENGTH];
	GASSERT(m_pcFileName);
	GASSERT(m_ptFileName);
	m_phFileHandle = nullptr;
}

GFile::~GFile()
{
	GSAFE_DELETE_ARRAY(m_pcFileName)
	GSAFE_DELETE_ARRAY(m_ptFileName)
}

bool GFile::Open(const TCHAR* fileName, FileAccess opType, FileMode fileMode)
{
	


}

bool GFile::Open(const CHAR* fileName, FileAccess opType, FileMode fileMode)
{
	if (opType != FileAccess::Write)
	{
		if (!FileIsExit(fileName))
			return false;
	}

	size_t pathStrLen = GStrLen(fileName);
	if (pathStrLen == 0 || pathStrLen >= MAX_PATH_LENGTH)
	{
		GOutputDebugStringW(TEXT("����·�����Ϸ���path string length:%d"), pathStrLen);
		return false;
	}

	GStrCpy(m_pcFileName, MAX_PATH_LENGTH, fileName);
	char filemode[FILE_MODE_BUFFER];

	switch(opType)
	{
	case FileAccess::Read:
		GStrCpy(filemode, FILE_MODE_BUFFER, "r");
	case FileAccess::ReadWrite:
		GStrCpy(filemode, FILE_MODE_BUFFER, "r+");
	case FileAccess::ReadWriteCreate:
		GStrCpy(filemode, FILE_MODE_BUFFER, "w+");
	case FileAccess::Write:
		GStrCpy(filemode, FILE_MODE_BUFFER, "w");
	}

	switch (fileMode)
	{
	case FileMode::BINARY:
		GStrCat(filemode, FILE_MODE_BUFFER, "b");
	case FileMode::TEXT:
		GStrCat(filemode, FILE_MODE_BUFFER, "t");
	}

	if (m_phFileHandle != NULL)
		fclose(m_phFileHandle);

	return fopen_s(&m_phFileHandle, m_pcFileName, filemode) == 0;
}

bool GFile::Close()
{
	if (m_phFileHandle != NULL)
		return fclose(m_phFileHandle) == 0;
	else
		return false;
}

/// <summary>
/// ǿ�Ƚ��������ڵ�����д���ļ�
/// </summary>
/// <returns></returns>
bool GFile::Flush()
{
	if (m_phFileHandle != NULL)
		return fflush(m_phFileHandle) == 0;
	else
		return false;
}

/// <summary>
/// дһ���ַ�����ָ�봦
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
bool GFile::WriteChar(char c)
{
	return putc(c, m_phFileHandle) == 0;
}

/// <summary>
/// ��ȡһ���ַ�����ָ����ǰ�ƶ�һλ
/// </summary>
/// <param name="c">��ȡ���ַ�</param>
/// <returns>��ȡ�Ƿ�ɹ�</returns>
bool GFile::ReadChar(char& c)
{
	c= getc(m_phFileHandle);
	return c != EOF;
}

bool GFile::Seek(StreamCurPos basePos, long offset)
{
	if (!IsOpen())
		return false;

	return fseek(m_phFileHandle, offset, (int)basePos) == 0;
}

bool GFile::WriteLine(StreamCurPos basePos, const TCHAR* str)
{
	if (!IsOpen()) 
	{
		GOutputDebugStringW(TEXT("�ļ�δ��"));
		return false;
	}
	if (str == nullptr)
	{
		GOutputDebugStringW(TEXT("д���ַ���Ϊ��"));
		return false;
	}
	const int strLen = GStrLen(str);
	char* buffer = GNEW char[strLen];
	GPTCHAR_To_PConstChar(str, buffer, strLen);
	BOOL res = fputs(buffer, m_phFileHandle) == 0;
	Flush();
	return res;
}

bool GFile::WriteLine(StreamCurPos basePos, const CHAR* str)
{
	BOOL res = fputs(str, m_phFileHandle) == 0;
	Flush();
	return res;
}

bool GFile::ReadLine(StreamCurPos basePos, int readMaxSize, TCHAR** outstr)
{
	if (!IsOpen())
		return false;

	Seek(basePos, 0);
	char* buffer = new char[readMaxSize];
	char* p = fgets(buffer, readMaxSize, m_phFileHandle);
	GPConstChar_To_PTCHAR(p, *outstr, readMaxSize);
	return p != NULL;
}

bool GFile::ReadLine(StreamCurPos basePos, int readMaxSize, CHAR** outstr)
{
	if (!IsOpen())
		return false;
	if (*outstr != nullptr)
		return false;
	Seek(basePos, 0);

	char* p = fgets(*outstr, readMaxSize, m_phFileHandle);
	return p != NULL;
}

bool GFile::ReadAll(TCHAR** outstr)
{
	if (!IsOpen())
		return false;
	if (*outstr != nullptr)
		return false;

	Seek(StreamCurPos::End, 0);
	long str_size = ftell(m_phFileHandle);
	Seek(StreamCurPos::Start, 0);
	char* buffer = new char[str_size];
	size_t readCount = fread(buffer, str_size, sizeof(char), m_phFileHandle);
    GPConstChar_To_PTCHAR(buffer,*outstr,str_size);
	
	return readCount == str_size;
}

bool GFile::ReadAll(CHAR** outstr)
{
	if (!IsOpen())
		return false;
	if (*outstr != nullptr)
		return false;

	Seek(StreamCurPos::End, 0);
	long str_size = ftell(m_phFileHandle);
	Seek(StreamCurPos::Start, 0);
	char* buffer = new char[str_size];
	size_t readCount = fread(buffer, str_size, sizeof(char), m_phFileHandle);
	GPConstChar_To_PTCHAR(buffer, *outstr, str_size);
	return readCount == str_size;
}

bool GFile::WriteAll(const CHAR* str)
{
	if (!IsOpen())
		return false;
	size_t strlen = GStrLen(str);

	GTempString<char> _outstr;
	_outstr.str = GPTCHAR_To_PConstChar(str);
	size_t writeCount = fwrite(_outstr.Get(), sizeof(char), strlen, m_pFileHandle);
	BOOL res = writeCount == 1;
	Flush();
	return res;
}

bool GFile::Delete()
{
	Close();
	int opcode = remove(m_phFileHandle);
	if (opcode == 0)
	{
		if (m_phFileHandle != nullptr)
			delete m_pFileHandle;
		if (m_pcfileName != nullptr)
			delete[] m_pcfileName;
	}

	return opcode == 0;

}















bool GFile::FileIsExit(const TCHAR* filePath)
{
	return PathFileExists(filePath);
}

bool GFile::FileIsExit(const CHAR* filePath)
{
	return PathFileExistsA(filePath);
}