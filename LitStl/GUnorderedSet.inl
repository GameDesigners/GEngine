//构造函数
//**********************************************************************************************************************************************

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::__GUnorderedSet() {}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::__GUnorderedSet(size_t bnum) : __hash_table(bnum) {}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::__GUnorderedSet(const __GUnorderedSet& cv)
{
	this->m_current_bucket_idx = cv.m_current_bucket_idx;
	this->m_count = cv.m_count;

}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::__GUnorderedSet(__GUnorderedSet&& rv)
{
	this->m_current_bucket_idx = rv.m_current_bucket_idx;
	this->m_count = rv.m_count;
	this->m_bucket=g_move(rv.m_bucket);

	rv.m_current_bucket_idx = 0;
	rv.m_count = 0;
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::__GUnorderedSet(iterator_type _begin, iterator_type _end)
{
	if (iterator_type p = _begin; p != _end; p++)
		this->__insert(*p);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::__GUnorderedSet(iterator_type _begin, iterator_type _end, size_t bnum)
{

}


//插入和删除
//*******************************************************************************************************************************************************************************************************************

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline GPair<typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::iterator_type, bool> GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::insert(const T& val)
{
	if (IsMulti)
	{
		node_pointer res = this->__insert(val);
		return GPair<typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::iterator_type, bool>(res, false);
	}
	else
	{
		node_pointer res = this->__search(val);
		if (res != nullptr)
			return GPair<typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::iterator_type, bool>(res, false);
		res = this->__insert(val);
		return GPair<typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::iterator_type, bool>(res, false);
	}
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::insert(iterator_type _begin, iterator_type _end)
{
	for (iterator_type p = _begin; p != _end; p++)
		insert(*p);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::insert(std::initializer_list<T> values)
{
	for (auto p = values.begin(); p != values.end(); p++)
		insert(*p);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
template<typename ...Args>
inline GPair<typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::iterator_type, bool> GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::emplace(Args ...args)
{
	return insert(T(args...));
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::earse(const T& val)
{
	this->__remove(val);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::earse(iterator_type pos)
{
	this->__remove(*pos);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::earse(iterator_type _begin, iterator_type _end)
{

	while (_begin!=_end)
		this->__remove(*(pos++));
}

//布局操作
//*******************************************************************************************************************************************************************************************************************
template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline ConflictHandlingFun GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::coflict_handling_function()
{
	return this->__get_conflict_handling_fun();
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline ExtractKey GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::hash_function()
{
	return this->__get_extract_key_fun();
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline EqualHashCode GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::hash_code_equals_function()
{
	return this->__get_hash_equals_fun();
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline size_t GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::bucket_count()
{
	return __get_current_bucket_count();
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline size_t GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::max_bucket_count()
{
	return this->__get_max_bucket_count();
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline float GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::load_factor()
{
	return this->__get_load_factor();
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline float GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::max_load_factor()
{
	return this->__max_load_factor();
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::set_max_load_factor(size_t max_factor)
{
	this->__max_load_factor() = max_factor;
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::rehash(size_t bnum)
{
	this->__rehash_table(bnum);
}