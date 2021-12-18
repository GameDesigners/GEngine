#ifndef GSTRINGS_H
#define GSTRINGS_H
#include "GContainer.h"
#include "GIterator.h"
namespace GEngine {
	namespace GStl {

		template<typename T>
		struct char_traist
		{

		};

		template<typename charT,typename traits=char_traist<charT>, GMemManagerFun MMFun= GMemObject::GetMemManager>
		class GSTL_API __base_string : public GContainer<charT>
		{
		public:
			typedef charT                            char_type;
			typedef charT*                           _string;
			typedef const charT*                     _cstring;

			typedef _SingleMemUnit_Iterator<charT>   iterator_type;
			typedef _SingleMemUnit_CIterator<charT>  c_iterator_type;
			typedef _SingleMemUnit_RIterator<charT>  r_iterator_type;
			typedef _SingleMemUnit_CRIterator<charT> cr_iterator_type;
		public:
			__base_string();
			__base_string(const __base_string& cv);
			__base_string(__base_string&& rv);
			__base_string(__base_string& str, size_t stridx);
			__base_string(__base_string& str, size_t stridx, size_t len);
			__base_string(_string cstr);
			__base_string(char_type chars[],size_t charslen);
			__base_string(size_t num, char_type c);
			__base_string(iterator_type _begin, iterator_type _end);
			__base_string(std::initializer_list<charT> values);

		//虚函数重写
		public:
			virtual bool empty();
			virtual size_t size();
			virtual void clear();

		private:
			virtual size_t capcity() { return 0; }
			_string m_data;
		};
#include "GStrings.inl"

		//全特化
		typedef __base_string<char>       GString;
		typedef __base_string<TCHAR>      GTString;
		typedef __base_string<wchar_t>    GWString;
		typedef __base_string<char16_t>   GU16String;
		typedef __base_string<char32_t>   GU32String;

	}
}
#endif // !GSTRINGS_H

