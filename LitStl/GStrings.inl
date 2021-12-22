#include "GStrings.h"
template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::char_type GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__nil = (charT)('\0');

//构造函数
//**********************************************************************************************************************************************

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string()
{
	__create_new_str_mem(StringDefaultBufferSize, m_first, m_last, m_end_of_storage);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(const __base_string& cv)
{
	assign(cv);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(__base_string&& rv)
{
	m_first = rv.m_first;
	m_last = rv.m_last;
	m_end_of_storage = rv.m_end_of_storage;

	rv.m_first = nullptr;
	rv.m_last = nullptr;
	rv.m_end_of_storage = nullptr;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(const __base_string& str, size_t stridx)
{
	assign(str, stridx);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(const __base_string& str, size_t stridx, size_t len)
{
	assign(str, stridx, len);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(char_type chars[])
{
	assign(chars);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(char_type chars[], size_t charslen)
{
	assign(chars, charslen);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(const char_type chars[])
{
	assign(chars);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(const char_type chars[], size_t charslen)
{
	assign(chars, charslen);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(size_t num, char_type c)
{
	assign(num, c);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(iterator_type _begin, iterator_type _end)
{
	size_t cpy_len = static_cast<size_t>(_end - _begin);//多了__nil
	__adjust_string_capcity(cpy_len);
	char_pointer p = m_first;

	int index = 0;
	for (iterator_type iter = _begin; iter != _end; iter++)
	{
		p[index] = *iter;
		index++;
	}

	p[index] = __nil;
	m_last = m_first + index;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(std::initializer_list<charT> values)
{
	size_t cpy_len = values.size();
	__adjust_string_capcity(cpy_len);
	int index = 0;
	for (auto p = values.begin(); p != values.end(); p++, index++)
		m_first[index] = *p;
	m_first[index] = __nil;
	m_last = m_first + index;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::~__base_string()
{
	clear();
}

//赋值函数
//**********************************************************************************************************************************************

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator=(const __base_string& cv)
{
	assign(cv);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator=(__base_string&& rv)
{
	clear();
	m_first = rv.m_first;
	m_last = rv.m_last;
	m_end_of_storage = rv.m_end_of_storage;

	rv.m_first = nullptr;
	rv.m_last = nullptr;
	rv.m_end_of_storage = nullptr;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::assign(const __base_string& cv)
{
	size_t cpy_len = cv.__caculate_current_string_size();
	size_t current_capcity = __adjust_string_capcity(cpy_len);
	GMemoryCpy(m_first, current_capcity * sizeof(charT), cv.m_first, cpy_len * sizeof(charT));
	m_last = m_first + cpy_len - 1;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::assign(const __base_string& str, size_t stridx)
{
	distance len = str.__caculate_current_string_size();
	if (stridx >= len)//索引stridx不合法
		__create_new_str_mem(StringDefaultBufferSize, m_first, m_last, m_end_of_storage);
	else
	{
		char_pointer cpy_start = str.m_first + stridx;
		size_t cpy_len = static_cast<size_t>(str.m_last - cpy_start + 1);
		size_t current_capcity = __adjust_string_capcity(cpy_len);
		GMemoryCpy(m_first, current_capcity * sizeof(charT), cpy_start, cpy_len * sizeof(charT));
		m_last = m_first + cpy_len - 1;
	}
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::assign(const __base_string& str, size_t stridx, size_t len)
{
	distance str_len = str.__caculate_current_string_size();
	if (stridx >= str_len)
		__create_new_str_mem(StringDefaultBufferSize, m_first, m_last, m_end_of_storage);

	char_pointer cpy_start = str.m_first + stridx;
	size_t remainder = static_cast<size_t>(str.m_last - cpy_start);
	size_t cpy_len = len <= remainder ? len : remainder;
	size_t current_capcity = __adjust_string_capcity(cpy_len);
	GMemoryCpy(m_first, current_capcity * sizeof(charT), cpy_start, cpy_len * sizeof(charT));
	*(m_first + cpy_len) = __nil;
	m_last = m_first + cpy_len;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::assign(char_type chars[])
{
	size_t char_arr_len = __str_len_functor(chars);
	size_t current_capcity = __adjust_string_capcity(char_arr_len);
	GMemoryCpy(m_first, current_capcity * sizeof(charT), chars, char_arr_len * sizeof(charT));
	m_first[char_arr_len] = __nil;
	m_last = m_first + char_arr_len;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::assign(char_type chars[], size_t charslen)
{
	size_t char_arr_len = __str_len_functor(chars);
	charslen = charslen <= char_arr_len ? charslen : char_arr_len;
	size_t current_capcity = __adjust_string_capcity(charslen);
	GMemoryCpy(m_first, current_capcity * sizeof(charT), chars, charslen * sizeof(charT));
	*(m_first + charslen) = __nil;
	m_last = m_first + charslen;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::assign(const char_type chars[])
{
	size_t char_arr_len = __str_len_functor(chars);
	size_t current_capcity = __adjust_string_capcity(char_arr_len);
	char_pointer cpy_start = const_cast<char_pointer>(chars);
	GMemoryCpy(m_first, current_capcity, cpy_start, char_arr_len);
	m_first[char_arr_len] = __nil;
	m_last = m_first + char_arr_len;
} 

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::assign(const char_type chars[], size_t charslen)
{
	size_t char_arr_len = __str_len_functor(chars);
	charslen = charslen <= char_arr_len ? charslen : char_arr_len;
	size_t current_capcity = __adjust_string_capcity(charslen);
	char_pointer cpy_start = const_cast<char_pointer>(chars);
	GMemoryCpy(m_first, current_capcity * sizeof(charT), cpy_start, charslen * sizeof(charT));
	*(m_first + charslen) = __nil;
	m_last = m_first + charslen;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::assign(size_t num, char_type c)
{
	size_t current_capcity = __adjust_string_capcity(num);
	char_pointer p = m_first;
	int index = 0;
	for (index = 0; index < num && p + 1 != m_end_of_storage; index++)
		p[index] = c;
	p[index] = __nil;
	m_last = m_first + index;
}


//安插和移除字符
//**********************************************************************************************************************************************

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator+=(const __base_string& str)
{
	size_t cpy_len = str.__caculate_current_string_size();
	size_t source_len = __caculate_current_string_size();
	size_t current_capcity = __adjust_string_capcity(cpy_len + source_len);
	size_t reminder_capcity = current_capcity - source_len;

	GMemoryCpy(m_last, reminder_capcity * sizeof(charT), str.m_first, cpy_len * sizeof(charT));
	m_last = m_last + cpy_len - 1;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator+=(const char_type& c)
{
	size_t current_str_len = __caculate_current_string_size();
	__adjust_string_capcity(current_str_len + 1);
	*m_last = c;
	m_last = m_last + 1;
	*m_last = __nil;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator+=(std::initializer_list<char_type> values)
{
	size_t current_str_len = __caculate_current_string_size();
	size_t cpy_len = values.size();
	__adjust_string_capcity(current_str_len + cpy_len);

	for (auto p = values.begin(); p != values.end(); p++)
	{
		*m_last = *p;
		m_last = m_last + 1;
	}
	*m_last = __nil;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::append(const __base_string& str)
{
	*this += str;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::append(const __base_string& str, size_t stridx)
{
	*this += __base_string(str, stridx);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::append(const __base_string& str, size_t stridx, size_t len)
{
	*this += __base_string(str, stridx, len);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::append(char_type chars[])
{
	*this += __base_string(chars);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::append(char_type chars[], size_t charslen)
{
	*this += __base_string(chars, charslen);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::append(size_t num, const char_type& c)
{
	*this += __base_string(num, c);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::push_back(const char_type& c)
{
	*this += c;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline __base_string<charT, GStrLenFun, MMFun>& GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::insert(size_t pos, size_t num, const char_type& c)
{
	size_t source_len = __caculate_current_string_size();
	if (pos >= source_len) {
		append(num, c);
		return *this;
	}
	size_t current_capcity = __adjust_string_capcity(source_len + num);
	char_pointer insert_pos = m_first + pos;
	char_pointer last = m_last;
	while (last != insert_pos - 1)
	{
		*(last + num) = *last;
		last--;
	}

	for (int index = 0; index < num; index++, insert_pos++)
		*insert_pos = c;
	m_last = m_last + num;
	return *this;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline __base_string<charT,GStrLenFun,MMFun>& GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::insert(size_t pos, const __base_string& str)
{
	size_t cpy_len = str.length();
	return insert(pos, str, cpy_len);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline __base_string<charT, GStrLenFun, MMFun>& GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::insert(size_t pos, const __base_string& str, size_t len)
{
	size_t dest_len = str.length();
	size_t cpy_len = len <= dest_len ? len : dest_len;
	size_t source_len = __caculate_current_string_size();
	size_t current_capcity = __adjust_string_capcity(cpy_len + source_len);
	char_pointer insert_pos = m_first + pos;
	char_pointer last = m_last;
	m_last = m_last + cpy_len;
	while (last != insert_pos - 1)
	{
		*(last + cpy_len) = *last;
		last--;
	}

	for (int index = 0; index < cpy_len; index++) {
		char_type c = str.m_first[index];
		insert_pos[index] = c;
	}
	return *this;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline __base_string<charT, GStrLenFun, MMFun>& GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::insert(size_t pos, const __base_string& str, size_t npos, size_t len)
{
	__base_string temp(str, npos, len);
	return insert(pos, temp);
}


//子字符串操作
//**********************************************************************************************************************************************

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline __base_string<charT, GStrLenFun, MMFun> GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::substr()
{
	return __base_string(*this);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline __base_string<charT, GStrLenFun, MMFun> GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::substr(size_t stridx)
{
	return __base_string(*this, stridx);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline __base_string<charT, GStrLenFun, MMFun> GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::substr(size_t stridx, size_t len)
{
	return __base_string(*this, stridx, len);
}


//搜索和查找
//**********************************************************************************************************************************************

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline size_t GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::find(const __base_string& child)
{
	//return __brute_force_substring_search(child);
	return __kmp_substring_search(child);
}



//元素访问
//**********************************************************************************************************************************************

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::char_reference GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator[](size_t idx)
{
	return m_first[idx];
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::char_reference GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::at(size_t idx)
{
	size_t str_len = size();
	GASSERT(idx < str_len);
	return m_first[idx];
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::char_reference GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::front()
{
	size_t str_len = size();
	GASSERT(str_len != 0);
	return m_first[0];
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::char_reference GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::back()
{
	size_t str_len = size();
	GASSERT(str_len != 0);
	return m_first[str_len - 1];
}

//虚函数重写
//**********************************************************************************************************************************************

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline bool GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator==(const __base_string& rhs) const
{
	char_pointer p = m_first;
	char_pointer q = rhs.m_first;

	while (*p!=__nil&&*q!=__nil)
	{
		if (*p != *q)
			return false;
		p++;
		q++;
	}

	return *p == __nil && *q == __nil;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline bool GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator!=(const __base_string& rhs) const
{
	return !(*this == rhs);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline bool GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator<(const __base_string& rhs) const
{
	char_pointer p = m_first;
	char_pointer q = rhs.m_first;

	while (*p != __nil && *q != __nil)
	{
		if (*p < *q)
			return true;
		p++;
		q++;
	}

	return *p == __nil && *q != __nil;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline bool GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator>(const __base_string& rhs) const
{
	char_pointer p = m_first;
	char_pointer q = rhs.m_first;

	while (*p != __nil && *q != __nil)
	{
		if (*p > *q)
			return true;
		p++;
		q++;
	}

	return *p != __nil && *q == __nil;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline bool GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator>=(const __base_string& rhs) const
{
	char_pointer p = m_first;
	char_pointer q = rhs.m_first;

	while (*p != __nil && *q != __nil)
	{
		if (*p > *q)
			return true;
		p++;
		q++;
	}

	return *p != __nil;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline bool GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator<=(const __base_string& rhs) const
{
	char_pointer p = m_first;
	char_pointer q = rhs.m_first;

	while (*p != __nil && *q != __nil)
	{
		if (*p < *q)
			return true;
		p++;
		q++;
	}

	return *q != __nil;
}



//虚函数重写
//**********************************************************************************************************************************************

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline size_t GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::capcity()
{
	if (m_first == nullptr && m_last == nullptr)
		return 0;
	else
		return m_end_of_storage - m_first;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline bool GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::empty()
{
	if (m_first == nullptr || *m_first == __nil)
		return true;
	else
		return false;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline size_t GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::size()
{
	if (m_first == nullptr || *m_first == __nil)
		return 0;
	else
		return m_last - m_first;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline void GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::clear()
{
	size_t current_capcity = __caculate_current_string_capcity();
	if (m_first != nullptr && current_capcity != 0)
		this->Delete(m_first, current_capcity, current_capcity);
	m_first = nullptr;
	m_last = nullptr;
	m_end_of_storage = nullptr;
}

//虚函数重写
//**********************************************************************************************************************************************

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::iterator_type GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::begin()
{
	return _SingleMemUnit_Iterator<charT>(m_first);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::iterator_type GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::end()
{
	return _SingleMemUnit_Iterator<charT>(m_last);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::c_iterator_type GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::cbegin()
{
	return _SingleMemUnit_CIterator<charT>(m_first);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::c_iterator_type GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::cend()
{
	return _SingleMemUnit_CIterator<charT>(m_last);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::r_iterator_type GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::rbegin()
{
	return _SingleMemUnit_RIterator<charT>(m_last - 1);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::r_iterator_type GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::rend()
{
	return _SingleMemUnit_RIterator<charT>(m_first-1);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::cr_iterator_type GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::crbegin()
{
	return _SingleMemUnit_CRIterator<charT>(m_last - 1);
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::cr_iterator_type GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::crend()
{
	return _SingleMemUnit_CRIterator<charT>(m_first - 1);
}



//子字符串查找算法:reference -> https://www.cnblogs.com/rude3knife/p/13531142.html
//**********************************************************************************************************************************************

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline size_t GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__brute_force_substring_search(const __base_string& pattern)
{
	size_t pattern_len = pattern.length();
	size_t source_len = length();
	char_pointer _pattern = pattern.m_first;
	char_pointer _source = m_first;
	for (int i = 0; i < source_len-pattern_len; i++)
	{
		for (int j = 0, k = i; j < pattern_len; j++, k++)
		{
			if (*(_source + k) != *(_pattern + j) && j != pattern_len - 1)
				break;
			if (*(_source + k) == *(_pattern + j) && j == pattern_len - 1)
				return i;				
		}
	}
	return -1;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline size_t GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__kmp_substring_search(const __base_string& pattern)
{
	size_t pattern_len = pattern.length();
	size_t source_len = length();
	char_pointer _pattern = pattern.m_first;
	char_pointer _source = m_first;
	//步骤1：构造部分匹配表
	int* partial_match_table = GNEW int[pattern_len];
	partial_match_table[0] = 0;  //无前缀后缀，共有元素长度为0
	for (int i = 1, j = 0; i < pattern_len; i++)
	{
		while (j > 0 && *(_pattern + j) != *(_pattern + i))
			j = partial_match_table[j - 1];

		if (*(_pattern + j) != *(_pattern + i))
			j++;
		partial_match_table[i] = j;
	}

	//步骤二：查找
	for (int i = 0, j = 0; i < source_len; i++) {
		while (j > 0 && *(_source + i) != *(_pattern+ j)) {
			j = partial_match_table[j - 1];
		}
		if (*(_source + i) == *(_pattern + j))
			j++;
		if (j == pattern_len) {
			GSAFE_DELETE_ARRAY(partial_match_table)
			return i - j + 1;
		}
	}
	GSAFE_DELETE_ARRAY(partial_match_table);
	return -1;
	
}