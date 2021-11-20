#ifndef GFILE_H
#define GFILE_H
#include "GSystem.h"
namespace GEngine
{
	namespace GSystem
	{
		/// <summary>
		/// �ļ���д��
		/// </summary>
		class GSYSTEM_API GFile
		{
		public:
			enum : unsigned int
			{
				MAX_PATH_LENGTH = 256,  //·����󳤶�
				FILE_MODE_BUFFER = 5,   //�ļ���ģʽ�ַ������峤��
				FILE_STEAM_BUFFER = 1024  //�ļ����ַ����黺���С
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
			/// ����·����ĳ���ļ�
			/// </summary>
			/// <param name="fileName">�ļ�·��</param>
			/// <param name="opType">��������/Ȩ��</param>
			/// <param name="fileMode">�ļ�ģʽ��������or�ı���</param>
			/// <returns>�Ƿ�򿪳ɹ�</returns>
			bool Open(const TCHAR* fileName, FileAccess opType, FileMode fileMode);
			/// <summary>
			

			/// <summary>
			/// ����·����ĳ���ļ�
			/// </summary>
			/// <param name="fileName">�ļ�·��</param>
			/// <param name="opType">��������/Ȩ��</param>
			/// <param name="fileMode">�ļ�ģʽ��������or�ı���</param>
			/// <returns>�Ƿ�򿪳ɹ�</returns>
			bool Open(const CHAR* fileName, FileAccess opType, FileMode fileMode);
			

			/// <summary>
			/// �ر��ļ�
			/// </summary>
			/// <returns>�ļ��Ƿ�رճɹ�</returns>
			bool Close();


			/// <summary>
			/// ǿ�ƽ��������ڵ�����д���ļ�
			/// </summary>
			/// <returns>ǿ��д���Ƿ�ɹ�</returns>
			bool Flush();


			/// <summary>
			/// ��ȡ�ļ��ı����ַ�����
			/// </summary>
			/// <returns>�ַ�������</returns>
			long GetFileStringLength();


			/// <summary>
			/// ��һ���ַ�д�뻺����
			/// </summary>
			/// <param name="c">�ַ�</param>
			/// <param name="basePos">����ָ���ƶ���basePos��Ĭ��ΪStreamCurPos::Current</param>
			/// <param name="offset">��ָ���basePos��ƫ���ַ�����Ĭ��Ϊ0</param>
			/// <returns>�Ƿ��ȡ�ɹ�</returns>
			bool WriteChar(char c, StreamCurPos basePos = StreamCurPos::Current, long offset = 0);


			/// <summary>
			/// �ӻ�������ȡһ���ַ�
			/// </summary>
			/// <param name="c">�������ַ�</param>
			/// <param name="basePos">����ָ���ƶ���basePos��Ĭ��ΪStreamCurPos::Current</param>
			/// <param name="offset">��ָ���basePos��ƫ���ַ�����Ĭ��Ϊ0</param>
			/// <returns>�Ƿ��ȡ�ɹ�</returns>
			bool ReadChar(char& c, StreamCurPos basePos = StreamCurPos::Current, long offset = 0);


			/// <summary>
			/// ��һ���ַ�д�뻺����
			/// </summary>
			/// <param name="c">�ַ�</param>
			/// <param name="basePos">����ָ���ƶ���basePos��Ĭ��ΪStreamCurPos::Current</param>
			/// <param name="offset">��ָ���basePos��ƫ���ַ�����Ĭ��Ϊ0</param>
			bool WriteChar(TCHAR tc, StreamCurPos basePos = StreamCurPos::Current, long offset = 0);


			/// <summary>
			/// �ӻ�������ȡһ���ַ�
			/// </summary>
			/// <param name="c">�������ַ�</param>
			/// <param name="basePos">����ָ���ƶ���basePos��Ĭ��ΪStreamCurPos::Current</param>
			/// <param name="offset">��ָ���basePos��ƫ���ַ�����Ĭ��Ϊ0</param>
			/// <returns>�Ƿ��ȡ�ɹ�</returns>
			bool ReadChar(TCHAR& tc, StreamCurPos basePos = StreamCurPos::Current, long offset = 0);


			/// <summary>
			/// ����ָ���ƶ���ĳ��λ��
			/// </summary>
			/// <param name="basePos">�ƶ�λ��</param>
			/// <param name="offset">���ƶ�λ����ǰƫ���ֽ���</param>
			/// <returns>�Ƿ��ƶ��ɹ�</returns>
			bool Seek(StreamCurPos basePos, long offset);


			/// <summary>
			/// д��һ�е��ļ���
			/// </summary>
			/// <param name="str">д���ַ���</param>
			/// <param name="basePos">����ָ���ƶ���basePos��Ĭ��ΪStreamCurPos::Current</param>
			/// <returns>�Ƿ�д��ɹ�</returns>
			bool WriteLine(const TCHAR* str, StreamCurPos basePos = StreamCurPos::Current);


			/// <summary>
			/// д��һ�е��ļ���
			/// </summary>
			/// <param name="str">д���ַ���</param>
			/// <param name="basePos">����ָ���ƶ���basePos��Ĭ��ΪStreamCurPos::Current</param>
			/// <returns>�Ƿ�д��ɹ�</returns>
			bool WriteLine(const CHAR* str, StreamCurPos basePos = StreamCurPos::Current);


			/// <summary>
			/// �����ж�ȡһ��
			/// </summary>
			/// <param name="outstr">>��ȡ�ַ�����</param>
			/// <param name="readMaxSize">��ȡ�ַ����黺��ĳ���</param>
			/// <param name="basePos">����ָ���ƶ���basePos��Ĭ��ΪStreamCurPos::Current</param>
			/// <returns>�Ƿ��ȡ�ɹ�</returns>
			bool ReadLine(TCHAR** outstr, int readMaxSize, StreamCurPos basePos = StreamCurPos::Current);


			/// <summary>
			/// �����ж�ȡһ��
			/// </summary>
			/// <param name="outstr">>��ȡ�ַ�����</param>
			/// <param name="readMaxSize">��ȡ�ַ����黺��ĳ���</param>
			/// <param name="basePos">����ָ���ƶ���basePos��Ĭ��ΪStreamCurPos::Current</param>
			/// <returns>�Ƿ��ȡ�ɹ�</returns>
			bool ReadLine(CHAR** outstr, int readMaxSize, StreamCurPos basePos);


			/// <summary>
			/// ��ȡ�ļ���ȫ��������TCHAR�ַ���
			/// </summary>
			/// <param name="outstr">����ַ�������</param>
			/// <returns>�Ƿ��ȡ�ɹ�</returns>
			bool ReadAll(TCHAR** outstr);


			/// <summary>
			/// ��ȡ�ļ���ȫ��������CHAR�ַ���
			/// </summary>
			/// <param name="outstr">����ַ�������</param>
			/// <returns>�Ƿ��ȡ�ɹ�</returns>
			bool ReadAll(CHAR** outstr);


			/// <summary>
			/// д���ַ���
			/// </summary>
			/// <param name="str"></param>
			/// <returns>�Ƿ�д��</returns>
			bool WriteAll(const TCHAR* str);


			/// <summary>
			/// д���ַ���
			/// </summary>
			/// <param name="str"></param>
			/// <returns>�Ƿ�д��</returns>
			bool WriteAll(const CHAR* str);


			/// <summary>
			///  ɾ�����ļ�
			/// </summary>
			/// <returns></returns>
			bool Delete();


			/// <summary>
			/// ���ļ��Ƿ����
			/// </summary>
			/// <param name="filePath">�ļ�·��</param>
			/// <returns>trueΪ���ڣ�falseΪ������</returns>
			static bool FileIsExit(const TCHAR* filePath);


			/// <summary>
			/// ���ļ��Ƿ����
			/// </summary>
			/// <param name="filePath">�ļ�·��</param>
			/// <returns>trueΪ���ڣ�falseΪ������</returns>
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
