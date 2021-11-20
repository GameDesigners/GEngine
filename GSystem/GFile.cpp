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
		GOutputDebugStringW(TEXT("GFile::Open传入的文件路径为空。"));
		return false;
	}
	ConvertToCString buffer(fileName);
	GStrCpy(m_pcFileName, MAX_PATH_LENGTH, buffer.result);
	GStrCpy(m_ptFileName, MAX_PATH_LENGTH, fileName);
	return open(opType, fileMode);
}

bool GFile::Open(const CHAR* fileName, FileAccess opType, FileMode fileMode)
{
	if (fileName == nullptr)
	{
		GOutputDebugStringW(TEXT("GFile::Open传入的文件路径为空。"));
		return false;
	}
	ConvertToTString buffer(fileName);
	GStrCpy(m_pcFileName, MAX_PATH_LENGTH, fileName);
	GStrCpy(m_ptFileName, MAX_PATH_LENGTH, buffer.result);
	return open(opType, fileMode);
}

bool GFile::Flush()
{
	if (m_phFileHandle != NULL)
		return fflush(m_phFileHandle) == 0;
	else
		return false;
}

long GFile::GetFileStringLength()
{
	if (!IsOpen())
		return false;

	Seek(StreamCurPos::End, 0);
	return ftell(m_phFileHandle);
}

bool GFile::WriteChar(char c,StreamCurPos basePos, long offset)
{
	Seek(basePos, offset);
	return putc(c, m_phFileHandle) == 0;
}

bool GFile::ReadChar(char& c, StreamCurPos basePos, long offset)
{
	Seek(basePos, offset);
	c = getc(m_phFileHandle);
	return c != EOF;
}

bool GFile::WriteChar(TCHAR tc, StreamCurPos basePos, long offset)
{
	Seek(basePos, 0);
	return putc(tc, m_phFileHandle) == 0;
}

bool GFile::ReadChar(TCHAR& tc, StreamCurPos basePos, long offset)
{
	Seek(basePos, offset);
	tc = getc(m_phFileHandle);
	return tc != EOF;
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
		GOutputDebugStringW(TEXT("文件未打开"));
		return false;
	}
	if (str == nullptr)
	{
		GOutputDebugStringW(TEXT("写入字符串为空"));
		return false;
	}
	ConvertToCString buffer(str);
	BOOL res = fputs(buffer.result, m_phFileHandle) == 0;
	res = res && fputc('\n', m_phFileHandle) == 0;
	Flush();
	return res;
}

bool GFile::WriteLine(const CHAR* str, StreamCurPos basePos)
{
	BOOL res = fputs(str, m_phFileHandle) == 0;
	res = res && fputc('\n', m_phFileHandle) == 0;
	Flush();
	return res;
}

bool GFile::ReadLine(TCHAR** outstr, int readMaxSize, StreamCurPos basePos)
{
	if (!IsOpen())
		return false;

	Seek(basePos, 0);
	char* read_buffer = GNEW char[readMaxSize];
	char* p = fgets(read_buffer, readMaxSize, m_phFileHandle);
	ConvertToTString buffer(read_buffer);
	GStrCpy(*outstr,readMaxSize,buffer.result);
	GSAFE_DELETE_ARRAY(read_buffer)
	return p != NULL;
}

bool GFile::ReadLine(CHAR** outstr, int readMaxSize, StreamCurPos basePos)
{
	if (!IsOpen())
		return false;
	if (outstr == nullptr)
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
	char* readBuffer = GNEW char[str_size];
	size_t readCount = fread(readBuffer, str_size, sizeof(char), m_phFileHandle);
	ConvertToTString buffer(readBuffer);
	GStrCpy(*outstr, GStrLen(*outstr), buffer.result);
	GSAFE_DELETE_ARRAY(readBuffer)
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

bool GFile::Close()
{
	if (m_phFileHandle != NULL)
		return fclose(m_phFileHandle) == 0;
	else
		return false;
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
		GOutputDebugStringW(TEXT("传入路径不合法，path string length:%d"), pathStrLen);
		return false;
	}

	//文件模式字符串
	char _mode[FILE_MODE_BUFFER] = { 0 };

	switch (opType)
	{
	case FileAccess::Read:
		GStrCpy(_mode, FILE_MODE_BUFFER, "r");
		break;
	case FileAccess::ReadWrite:
		GStrCpy(_mode, FILE_MODE_BUFFER, "r+");
		break;
	case FileAccess::ReadWriteCreate:
		GStrCpy(_mode, FILE_MODE_BUFFER, "w+");
		break;
	case FileAccess::Write:
		GStrCpy(_mode, FILE_MODE_BUFFER, "w");
		break;
	}

	switch (fileMode)
	{
	case FileMode::BINARY:
		GStrCat(_mode, FILE_MODE_BUFFER, "b");
		break;
	case FileMode::TEXT:
		GStrCat(_mode, FILE_MODE_BUFFER, "t");
		break;
	}

	if (m_phFileHandle != NULL)
		fclose(m_phFileHandle);

	return fopen_s(&m_phFileHandle, m_pcFileName, _mode) == 0;
}


bool GFile::FileIsExit(const TCHAR* filePath)
{
	return PathFileExists(filePath);
}

bool GFile::FileIsExit(const CHAR* filePath)
{
	return PathFileExistsA(filePath);
}