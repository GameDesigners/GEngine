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
	if (fileName == nullptr)
	{
		GOutputDebugStringW(TEXT("GFile::Open������ļ�·��Ϊ�ա�"));
		return false;
	}
	GPTCHAR_To_PConstChar(fileName, m_pcFileName, MAX_PATH_LENGTH);
	GStrCpy(m_ptFileName, MAX_PATH_LENGTH, fileName);
	return open(opType, fileMode);
}

bool GFile::Open(const CHAR* fileName, FileAccess opType, FileMode fileMode)
{
	GPConstChar_To_PTCHAR(fileName, m_ptFileName, MAX_PATH_LENGTH);
	GStrCpy(m_pcFileName, MAX_PATH_LENGTH, fileName);
	return open(opType, fileMode);
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

bool GFile::WriteLine(const TCHAR* str, StreamCurPos basePos)
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
	GSAFE_DELETE_ARRAY(buffer)
	Flush();
	return res;
}

bool GFile::WriteLine(const CHAR* str, StreamCurPos basePos)
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
	char* buffer = GNEW char[readMaxSize];
	char* p = fgets(buffer, readMaxSize, m_phFileHandle);
	GPConstChar_To_PTCHAR(p, *outstr, readMaxSize);
	GSAFE_DELETE_ARRAY(buffer)
	return p != NULL;
}

bool GFile::ReadLine(StreamCurPos basePos, int readMaxSize, CHAR** outstr)
{
	if (!IsOpen())
		return false;
	if (outstr == nullptr)
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
	char* buffer = GNEW char[str_size];
	size_t readCount = fread(buffer, str_size, sizeof(char), m_phFileHandle);
    GPConstChar_To_PTCHAR(buffer,*outstr,str_size);
	GSAFE_DELETE_ARRAY(buffer)
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
	char* buffer = GNEW char[str_size];
	size_t readCount = fread(buffer, str_size, sizeof(char), m_phFileHandle);
	GStrCpy(*outstr, GStrLen(*outstr), buffer);
	GSAFE_DELETE_ARRAY(buffer)
	return readCount == str_size;
}

bool GFile::WriteAll(const TCHAR* str)
{
	if (!IsOpen())
		return false;
	size_t strlen = GStrLen(str);

	char* buffer = GNEW char[strlen];
	GPTCHAR_To_PConstChar(str,buffer,strlen);
	size_t writeCount = fwrite(buffer, sizeof(char), strlen, m_phFileHandle);
	BOOL res = writeCount == 1;
	Flush();
	GSAFE_DELETE_ARRAY(buffer)
	return res;
}

bool GFile::WriteAll(const CHAR* str)
{
	if (!IsOpen())
		return false;
	size_t strlen = GStrLen(str);
	size_t writeCount = fwrite(str, sizeof(char), strlen, m_phFileHandle);
	BOOL res = writeCount == 1;
	Flush();
	return res;
}

bool GFile::Delete()
{
	Close();
	int opcode = remove(m_pcFileName);
	if (opcode == 0)
	{
		GSAFE_DELETE_ARRAY(m_pcFileName)
		GSAFE_DELETE_ARRAY(m_ptFileName)
	}

	return opcode == 0;

}


bool GFile::open(FileAccess opType, FileMode fileMode)
{
	if (opType == FileAccess::Read)
	{
		if (!FileIsExit(m_pcFileName))
			return false;
	}

	size_t pathStrLen = GStrLen(m_pcFileName);
	if (pathStrLen == 0 || pathStrLen >= MAX_PATH_LENGTH)
	{
		GOutputDebugStringW(TEXT("����·�����Ϸ���path string length:%d"), pathStrLen);
		return false;
	}

	char filemode[FILE_MODE_BUFFER] = { 0 };

	switch (opType)
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


bool GFile::FileIsExit(const TCHAR* filePath)
{
	return PathFileExists(filePath);
}

bool GFile::FileIsExit(const CHAR* filePath)
{
	return PathFileExistsA(filePath);
}