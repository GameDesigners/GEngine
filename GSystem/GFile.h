#ifndef GFILE_H
#define GFILE_H
#include "GSystem.h"
namespace GEngine
{
	namespace GSystem
	{
		/// <summary>
		/// 文件读写类
		/// </summary>
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

		protected:
			class ConvertToTString
			{
			public:
				ConvertToTString(const CHAR* source)
				{
					size_t size = MultiByteToWideChar(CP_ACP, 0, source, -1, NULL, 0);
					ULONGLONG len = sizeof(TCHAR) * size;
					result = new TCHAR[len];
					MultiByteToWideChar(CP_ACP, 0, (LPCCH)source, -1, (LPWSTR)result, len);
				}

				~ConvertToTString()
				{
					GSAFE_DELETE_ARRAY(result)
				}

			public:
				TCHAR* result = nullptr;
			};
			class ConvertToCString
			{
			public:
				ConvertToCString(const TCHAR* source)
				{
					size_t size = WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)source, -1, NULL, 0, NULL, FALSE);
					result = new char[sizeof(char) * size];
					WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)source, -1, (LPSTR)result, size, NULL, FALSE);
				}

				~ConvertToCString()
				{
					GSAFE_DELETE_ARRAY(result)
				}

			public:
				CHAR* result = nullptr;
			};

		public:
			GFile();
			~GFile();

			inline bool IsOpen() { return m_phFileHandle != nullptr; }
			inline bool IsPointerAtEndPos() { return feof(m_phFileHandle); }
			inline int GetLastErrorCode() { return ferror(m_phFileHandle); }
			
			/// <summary>
			/// 根据路径打开某个文件
			/// </summary>
			/// <param name="fileName">文件路径</param>
			/// <param name="opType">操作类型/权限</param>
			/// <param name="fileMode">文件模式【二进制or文本】</param>
			/// <returns>是否打开成功</returns>
			bool Open(const TCHAR* fileName, FileAccess opType, FileMode fileMode);
			/// <summary>
			

			/// <summary>
			/// 根据路径打开某个文件
			/// </summary>
			/// <param name="fileName">文件路径</param>
			/// <param name="opType">操作类型/权限</param>
			/// <param name="fileMode">文件模式【二进制or文本】</param>
			/// <returns>是否打开成功</returns>
			bool Open(const CHAR* fileName, FileAccess opType, FileMode fileMode);
			

			/// <summary>
			/// 关闭文件
			/// </summary>
			/// <returns>文件是否关闭成功</returns>
			bool Close();


			/// <summary>
			/// 强制将缓冲区内的数据写回文件
			/// </summary>
			/// <returns>强制写入是否成功</returns>
			bool Flush();


			/// <summary>
			/// 获取文件文本中字符数量
			/// </summary>
			/// <returns>字符串数量</returns>
			long GetFileStringLength();


			/// <summary>
			/// 将一个字符写入缓冲区
			/// </summary>
			/// <param name="c">字符</param>
			/// <param name="basePos">将流指针移动至basePos，默认为StreamCurPos::Current</param>
			/// <param name="offset">流指针从basePos处偏移字符数，默认为0</param>
			/// <returns>是否读取成功</returns>
			bool WriteChar(char c, StreamCurPos basePos = StreamCurPos::Current, long offset = 0);


			/// <summary>
			/// 从缓冲区读取一个字符
			/// </summary>
			/// <param name="c">读到的字符</param>
			/// <param name="basePos">将流指针移动至basePos，默认为StreamCurPos::Current</param>
			/// <param name="offset">流指针从basePos处偏移字符数，默认为0</param>
			/// <returns>是否读取成功</returns>
			bool ReadChar(char& c, StreamCurPos basePos = StreamCurPos::Current, long offset = 0);


			/// <summary>
			/// 将一个字符写入缓冲区
			/// </summary>
			/// <param name="c">字符</param>
			/// <param name="basePos">将流指针移动至basePos，默认为StreamCurPos::Current</param>
			/// <param name="offset">流指针从basePos处偏移字符数，默认为0</param>
			bool WriteChar(TCHAR tc, StreamCurPos basePos = StreamCurPos::Current, long offset = 0);


			/// <summary>
			/// 从缓冲区读取一个字符
			/// </summary>
			/// <param name="c">读到的字符</param>
			/// <param name="basePos">将流指针移动至basePos，默认为StreamCurPos::Current</param>
			/// <param name="offset">流指针从basePos处偏移字符数，默认为0</param>
			/// <returns>是否读取成功</returns>
			bool ReadChar(TCHAR& tc, StreamCurPos basePos = StreamCurPos::Current, long offset = 0);


			/// <summary>
			/// 将流指针移动至某个位置
			/// </summary>
			/// <param name="basePos">移动位置</param>
			/// <param name="offset">将移动位置向前偏移字节数</param>
			/// <returns>是否移动成功</returns>
			bool Seek(StreamCurPos basePos, long offset);


			/// <summary>
			/// 写入一行到文件流
			/// </summary>
			/// <param name="str">写入字符串</param>
			/// <param name="basePos">将流指针移动至basePos，默认为StreamCurPos::Current</param>
			/// <returns>是否写入成功</returns>
			bool WriteLine(const TCHAR* str, StreamCurPos basePos = StreamCurPos::Current);


			/// <summary>
			/// 写入一行到文件流
			/// </summary>
			/// <param name="str">写入字符串</param>
			/// <param name="basePos">将流指针移动至basePos，默认为StreamCurPos::Current</param>
			/// <returns>是否写入成功</returns>
			bool WriteLine(const CHAR* str, StreamCurPos basePos = StreamCurPos::Current);


			/// <summary>
			/// 从流中读取一行
			/// </summary>
			/// <param name="outstr">>读取字符数组</param>
			/// <param name="readMaxSize">读取字符数组缓冲的长度</param>
			/// <param name="basePos">将流指针移动至basePos，默认为StreamCurPos::Current</param>
			/// <returns>是否读取成功</returns>
			bool ReadLine(TCHAR** outstr, int readMaxSize, StreamCurPos basePos = StreamCurPos::Current);


			/// <summary>
			/// 从流中读取一行
			/// </summary>
			/// <param name="outstr">>读取字符数组</param>
			/// <param name="readMaxSize">读取字符数组缓冲的长度</param>
			/// <param name="basePos">将流指针移动至basePos，默认为StreamCurPos::Current</param>
			/// <returns>是否读取成功</returns>
			bool ReadLine(CHAR** outstr, int readMaxSize, StreamCurPos basePos);


			/// <summary>
			/// 读取文件的全部内容至TCHAR字符串
			/// </summary>
			/// <param name="outstr">输出字符串数组</param>
			/// <returns>是否读取成功</returns>
			bool ReadAll(TCHAR** outstr);


			/// <summary>
			/// 读取文件的全部内容至CHAR字符串
			/// </summary>
			/// <param name="outstr">输出字符串数组</param>
			/// <returns>是否读取成功</returns>
			bool ReadAll(CHAR** outstr);


			/// <summary>
			/// 写入字符串
			/// </summary>
			/// <param name="str"></param>
			/// <returns>是否写入</returns>
			bool WriteAll(const TCHAR* str);


			/// <summary>
			/// 写入字符串
			/// </summary>
			/// <param name="str"></param>
			/// <returns>是否写入</returns>
			bool WriteAll(const CHAR* str);


			/// <summary>
			///  删除此文件
			/// </summary>
			/// <returns></returns>
			bool Delete();


			/// <summary>
			/// 该文件是否存在
			/// </summary>
			/// <param name="filePath">文件路径</param>
			/// <returns>true为存在；false为不存在</returns>
			static bool FileIsExit(const TCHAR* filePath);


			/// <summary>
			/// 该文件是否存在
			/// </summary>
			/// <param name="filePath">文件路径</param>
			/// <returns>true为存在；false为不存在</returns>
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
