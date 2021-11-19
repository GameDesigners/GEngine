#ifndef GFILE_H
#define GFILE_H
#include "GSystem.h"
namespace GEngine
{
	namespace GSystem
	{
		class GSYSTEM_API GFile
		{
		public:
			enum : unsigned int
			{
				MAX_PATH_LENGTH = 256,  //路径最大长度
				FILE_MODE_BUFFER = 5,   //文件打开模式字符串缓冲长度
				FILE_STEAM_BUFFER = 1024  //文件流字符数组缓冲大小
			};

			enum class FileAccess
			{
				Read,
				Write,
				ReadWrite,
				ReadWriteCreate
			};

			enum class FileMode
			{
				TEXT,
				BINARY
			};

			enum class StreamCurPos : unsigned int
			{
				Start = SEEK_SET,
				Current = SEEK_CUR,
				End = SEEK_END
			};

		public:
			GFile();
			~GFile();

			inline bool IsOpen() { return m_phFileHandle != nullptr; }
			inline bool IsPointerAtEndPos() { return feof(m_phFileHandle); }
			inline int GetLastErrorCode() { return ferror(m_phFileHandle); }

			bool Open(const TCHAR* fileName, FileAccess opType, FileMode fileMode);
			bool Open(const CHAR* fileName, FileAccess opType, FileMode fileMode);
			bool Close();
			bool Flush();
			bool WriteChar(char c);
			bool ReadChar(char& c);
			bool Seek(StreamCurPos basePos, long offset);
			bool WriteLine(const TCHAR* str, StreamCurPos basePos = StreamCurPos::Current);
			bool WriteLine(const CHAR* str, StreamCurPos basePos = StreamCurPos::Current);
			bool ReadLine(StreamCurPos basePos, int readMaxSize, TCHAR** outstr);
			bool ReadLine(StreamCurPos basePos, int readMaxSize, CHAR** outstr);
			bool ReadAll(TCHAR** outstr);
			bool ReadAll(CHAR** outstr);
			bool WriteAll(const TCHAR* str);
			bool WriteAll(const CHAR* str);
			bool Delete();

			static bool FileIsExit(const TCHAR* filePath);
			static bool FileIsExit(const CHAR* filePath);

		private:
			PCHAR  m_pcFileName;
			PTCHAR m_ptFileName;
			FILE*  m_phFileHandle;

			bool open(FileAccess opType, FileMode fileMode);

		};
	}
}
#endif // !GFILE_H
