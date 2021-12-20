#ifndef GSTRINGS_H
#define GSTRINGS_H
#include "GContainer.h"
#include "GIterator.h"
namespace GEngine {
	namespace GStl {

		template<class charT> struct GStrLenFuntor
		{
			size_t operator()(const charT* str)
			{
				return GStrLen(str);
			}
		};

		template<typename charT, typename GStrLenFun, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API __base_string : public GContainer<charT>
		{
		public:
			typedef charT                            char_type;
			typedef charT*                           _string;
			typedef charT&                           char_reference;
			typedef charT*                           char_pointer;
			typedef const charT* _cstring;

			typedef ptrdiff_t                        distance;

			typedef _SingleMemUnit_Iterator<charT>   iterator_type;
			typedef _SingleMemUnit_CIterator<charT>  c_iterator_type;
			typedef _SingleMemUnit_RIterator<charT>  r_iterator_type;
			typedef _SingleMemUnit_CRIterator<charT> cr_iterator_type;

			enum
			{
				StringDefaultBufferSize = 24,
				StringDefaultIncreaseSize = 24,
			};

		public:
			__base_string();
			__base_string(const __base_string& cv);
			__base_string(__base_string&& rv);
			__base_string(const __base_string& str, size_t stridx);
			__base_string(const __base_string& str, size_t stridx, size_t len);
			__base_string(char_type chars[]);
			__base_string(char_type chars[], size_t charslen);  //char_pointer type
			__base_string(const char_type chars[]);             //const char_pointer type
			__base_string(const char_type chars[], size_t charslen);
			__base_string(size_t num, char_type c);
			__base_string(iterator_type _begin, iterator_type _end);
			__base_string(std::initializer_list<charT> values);
			~__base_string();

		//��ֵ����
		public:
			void operator=(const __base_string& cv);
			void operator=(__base_string&& rv);
			void assign(const __base_string& cv);
			void assign(const __base_string& str, size_t stridx);
			void assign(const __base_string& str, size_t stridx, size_t len);
			void assign(char_type chars[]);
			void assign(char_type chars[], size_t charslen);
			void assign(const char_type chars[]);
			void assign(const char_type chars[], size_t charslen);
			void assign(size_t num, char_type c);
			
		//C-Style �ַ����Ļ�ȡ
		public:
			const char_pointer c_str() const { if (m_first == nullptr) return &__nil; return m_first; }
			const char_pointer data() const { if (m_first == nullptr) return &__nil; return m_first; }

		//������Ƴ��ַ�
		public:
			void operator+=(const __base_string& str);
			void operator+=(const char_type& c);
			void operator+=(std::initializer_list<char_type> values);
			void append(const __base_string& str);
			void append(const __base_string& str, size_t stridx);
			void append(const __base_string& str, size_t stridx, size_t len);
			void append(char_type chars[]);
			void append(char_type chars[], size_t charslen);
			void append(const char_type chars[]);
			void append(const char_type chars[], size_t charslen);
			void append(size_t num, const char_type& c);
			void push_back(const char_type& c);
			__base_string& insert(size_t pos, size_t num, const char_type& c);
			__base_string& insert(size_t pos, const __base_string& str);
			__base_string& insert(size_t pos, const __base_string& str, size_t len);
			__base_string& insert(size_t pos, const __base_string& str, size_t npos, size_t len);

		//���ַ�������
		public:
			__base_string substr();
			__base_string substr(size_t stridx);
			__base_string substr(size_t stridx, size_t len);

		//�����Ͳ���
		public:
			size_t find(const __base_string& child);
			size_t rfind(const __base_string& child);
			size_t find_first_of(const __base_string& child);
			size_t find_last_of(const __base_string& child);
			size_t find_first_not_of(const __base_string& child);
			size_t find_last_not_of(const __base_string& child);


		//Ԫ�ط���
		public:
			char_reference operator[](size_t idx);
			char_reference at(size_t idx);
			char_reference front();
			char_reference back();

		//���������
		public:
			bool operator==(const __base_string& rhs) const;
			bool operator!=(const __base_string& rhs) const;
			bool operator<(const __base_string& rhs)  const;
			bool operator>(const __base_string& rhs)  const;
			bool operator>=(const __base_string& rhs) const;
			bool operator<=(const __base_string& rhs) const;

		//�麯����д
		public:
			virtual size_t capcity();
			virtual bool empty();
			virtual size_t size();
			virtual void clear();

			size_t length() const
			{
				if (m_first == nullptr || *m_first == __nil)
					return 0;
				else
					return m_last - m_first;
			}
			void erase() { clear(); }

		//������
		public:
			iterator_type   begin();
			iterator_type   end();
			c_iterator_type  cbegin();
			c_iterator_type  cend();
			r_iterator_type  rbegin();
			r_iterator_type  rend();
			cr_iterator_type crbegin();
			cr_iterator_type crend();

		private:
			inline void __create_new_str_mem(size_t len, char_pointer& _first, char_pointer& _last, char_pointer& _endofstorage)
			{
				char_pointer new_mem = this->New(len);
				GASSERT(new_mem != nullptr);
				_first = new_mem;
				*_first = '\0';
				m_last = _first;
				_endofstorage = new_mem + len;
			}
			inline size_t __adjust_string_capcity(size_t target_len)
			{
				if (m_first == nullptr && m_last == nullptr && m_end_of_storage == nullptr)
				{
					//����һ���µ��ڴ�飨ԭ�Ȳ����ڣ�
					size_t current_capcity = StringDefaultBufferSize;
					while (current_capcity <= target_len)
						current_capcity += StringDefaultIncreaseSize;
					__create_new_str_mem(current_capcity, m_first, m_last, m_end_of_storage);
					return current_capcity;
				}

				size_t current_capcity = __caculate_current_string_capcity();
				if (current_capcity > target_len)
					return current_capcity;//����Ҫ����

				size_t current_len = __caculate_current_string_size();
				size_t old_capcity = current_capcity;
				while (current_capcity <= target_len)
					current_capcity += StringDefaultIncreaseSize;//ÿ�ε��ӵ�������ֱ������Ŀ�곤�ȼ���

				char_pointer new_mem = this->New(current_capcity);
				GASSERT(new_mem != nullptr);
				GMemoryCpy(new_mem, current_capcity, m_first, current_len);//��ԭ���ڴ�����ݸ��Ƶ��µ��ڴ���
				this->Delete(m_first, old_capcity, old_capcity);

				m_first = new_mem;
				m_last = new_mem + current_len - 1;
				m_end_of_storage = new_mem + current_capcity;
				return current_capcity;
			}
			inline size_t __caculate_current_string_size() const { if (m_first == nullptr) return 0; return static_cast<size_t>(m_last - m_first + 1); }
			inline size_t __caculate_current_string_capcity() const { if (m_first == nullptr) return 0; return static_cast<size_t>(m_end_of_storage - m_first); }

			//�ַ������ҷ���
			inline size_t __brute_force_substring_search(const __base_string& pattern);


			char_pointer  m_first=nullptr;
			char_pointer  m_last = nullptr;
			char_pointer  m_end_of_storage = nullptr;
			GStrLenFun    __str_len_functor;   //�����ַ������ȵķº�������������β�ַ���0��
			static char_type     __nil;
		};

		//ȫ�ػ�
		typedef __base_string<char, GStrLenFuntor<char>>           GString;
		typedef __base_string<TCHAR, GStrLenFuntor<TCHAR>>         GTString;
		typedef __base_string<wchar_t, GStrLenFuntor<wchar_t>>     GWString;
		typedef __base_string<char16_t, GStrLenFuntor<char16_t>>   GU16String;
		typedef __base_string<char32_t, GStrLenFuntor<char16_t>>   GU32String;

#include "GStrings.inl"	
	}
}
#endif // !GSTRINGS_H

