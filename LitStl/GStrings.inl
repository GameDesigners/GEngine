template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
typename GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::char_type GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::m_nil = '\0';

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
	m_first = nullptr;
	m_last = nullptr;
	m_end_of_storage = nullptr;

	distance len = cv.m_last - cv.m_first;  //字符长度
	size_t current_capcity = __adjust_string_capcity(len);
	GMemoryCpy(m_first, current_capcity, cv.m_first, len);
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
	distance len = str.m_last - str.m_first;
	if (stridx >= len)//索引stridx不合法
		__create_new_str_mem(StringDefaultBufferSize, m_first, m_last, m_end_of_storage);
	else
	{
		char_pointer cpy_start = str.m_first + stridx;
		size_t cpy_len = static_cast<size_t>(str.m_last - cpy_start);
		size_t current_capcity = __adjust_string_capcity(cpy_len);
		GMemoryCpy(m_first, current_capcity, cpy_start, cpy_len);
		m_last = m_first + cpy_len;
	}
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(const __base_string& str, size_t stridx, size_t len)
{
	distance str_len = str.m_last - str.m_first;
	if (stridx >= str_len)
		__create_new_str_mem(StringDefaultBufferSize, m_first, m_last, m_end_of_storage);

	char_pointer cpy_start = str.m_first + stridx;
	size_t remainder = static_cast<size_t>(str.m_last - cpy_start);
	size_t cpy_len = len <= remainder ? len : remainder;
	size_t current_capcity = __adjust_string_capcity(cpy_len);
	GMemoryCpy(m_first, current_capcity, cpy_start, cpy_len);
	m_last = m_first + cpy_len;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(const _string cstr)
{
	size_t cstr_len = __str_len_functor(cstr);
	size_t current_capcity = __adjust_string_capcity(cstr_len);
	GMemoryCpy(m_first, current_capcity, cstr, cstr_len);
	m_last = m_first + cstr_len;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(const char_type chars[])
{
	size_t char_arr_len = __str_len_functor(chars);
	size_t current_capcity = __adjust_string_capcity(char_arr_len);
	char_pointer cpy_start = const_cast<char_pointer>(chars);
	GMemoryCpy(m_first, current_capcity, cpy_start, char_arr_len);
	m_first[char_arr_len] = '\0';
	m_last = m_first + char_arr_len + 1;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(const char_type chars[], size_t charslen)
{
	size_t char_arr_len = __str_len_functor(chars);
	charslen = charslen <= char_arr_len ? charslen : char_arr_len;
	size_t current_capcity = __adjust_string_capcity(charslen);
	GMemoryCpy(m_first, current_capcity, chars, charslen);
	m_last = m_first + charslen;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(size_t num, char_type c)
{
	size_t current_capcity = __adjust_string_capcity(num + 1);
	char_pointer p = m_first;
	int index = 0;
	for (index = 0; index < num && p + 1 != m_end_of_storage; index++)
		p[index] = c;
	p[index] = '\0';
	m_last = m_first + index + 1;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(iterator_type _begin, iterator_type _end)
{
	size_t cpy_len = static_cast<size_t>(_end - _begin);
	__adjust_string_capcity(cpy_len);
	char_pointer p = m_first;

	int index = 0;
	for (iterator_type iter = _begin; iter != _end; iter++)
	{
		p[index] = *iter;
		index++;
	}
	p[index] = '\0';
	m_last = m_first + index + 1;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::__base_string(std::initializer_list<charT> values)
{
	size_t cpy_len = values.size();
	__adjust_string_capcity(cpy_len);
	int index = 0;
	for (auto p = values.begin(); p != values.end(); p++, index++)
		m_first[index] = *p;
	m_first[index] = '\0';
	m_last = m_first + index + 1;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::~__base_string()
{
	clear();
}

//元素访问
//**********************************************************************************************************************************************
template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline charT& GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::operator[](size_t idx)
{
	return m_first[idx];
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
	if (m_first == nullptr || *m_first == '\0')
		return true;
	else
		return false;
}

template<typename charT, typename GStrLenFun, GMemManagerFun MMFun>
inline size_t GEngine::GStl::__base_string<charT, GStrLenFun, MMFun>::size()
{
	if (m_first == nullptr || *m_first == '\0')
		return 0;
	else
		return m_last - m_first - 1; //减去'\0'
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
