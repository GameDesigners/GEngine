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
	for (int index = 0; index < cv.m_bucket.size(); index++)
	{
		node_pointer p = cv.m_bucket[index];
		while (p!=nullptr)
			insert(p->key);
	}
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline GEngine::GStl::__GUnorderedSet<T,ExtractKey,ConflictHandlingFun,  EqualHashCode,MMFun,IsMulti>::__GUnorderedSet(__GUnorderedSet&& rv)
{
	this->m_max_load_factor = rv.m_max_load_factor;
	this->m_current_bucket_idx = rv.m_current_bucket_idx;
	this->m_count = rv.m_count;
	this->m_bucket=g_move(rv.m_bucket);

	rv.m_current_bucket_idx = 0;
	rv.m_count = 0;
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::__GUnorderedSet(iterator_type _begin, iterator_type _end)
{
	for(iterator_type p = _begin; p != _end; p++)
		this->__insert(*p);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::__GUnorderedSet(iterator_type _begin, iterator_type _end, size_t bnum):__hash_table(bnum)
{
	for(iterator_type p = _begin; p != _end; p++)
		this->__insert(*p);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::__GUnorderedSet(std::initializer_list<T> values)
{
	for(auto p=values.begin();p!=values.end();p++)
		this->__insert(*p);
}

//赋值函数
//*******************************************************************************************************************************************************************************************************************

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::operator=(const __GUnorderedSet& cv)
{
	clear();
	this->m_current_bucket_idx = cv.m_current_bucket_idx;
	for (int index = 0; index < cv.m_bucket.size(); index++)
	{
		node_pointer p = cv.m_bucket[index];
		while (p != nullptr)
			insert(p->key);
	}
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::operator=(__GUnorderedSet&& rv)
{
	clear();
	this->m_max_load_factor = rv.m_max_load_factor;
	this->m_current_bucket_idx = rv.m_current_bucket_idx;
	this->m_count = rv.m_count;
	this->m_bucket = g_move(rv.m_bucket);

	rv.m_current_bucket_idx = 0;
	rv.m_count = 0;
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::operator=(std::initializer_list<T> values)
{
	clear();
	for (auto p = values.begin(); p != values.end(); p++)
		this->__insert(*p);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::swap(__GUnorderedSet& v)
{
	float temp_max_load_factor = v.m_max_load_factor;
	size_t temp_bucket_idx = v.m_current_bucket_idx;
	size_t temp_count = v.m_count;
	GVector<node_pointer> temp_bucket = g_move(v.m_bucket);

	v.m_max_load_factor = this->m_max_load_factor;
	v.m_current_bucket_idx = this->m_current_bucket_idx;
	v.m_count = this->m_count;
	v.m_bucket = g_move(this->m_bucket);

	this->m_max_load_factor = temp_max_load_factor;
	this->m_current_bucket_idx = temp_bucket_idx;
	this->m_count = temp_count;
	this->m_bucket = g_move(temp_bucket);
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
		this->__remove(*(_begin++));
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
	return this->__get_current_bucket_count();
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

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::begin(size_t buckidx)
{
	if (buckidx < this->m_bucket.size())
		return _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(this->m_bucket[buckidx], &this->m_bucket);
	return _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(nullptr, &this->m_bucket);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::end(size_t buckidx)
{
	if (buckidx < this->m_bucket.size()) {
		node_pointer p = this->m_bucket[buckidx];
		while (p->next != nullptr)p = p->next;
		return _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(p, &this->m_bucket);
	}
	return _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(nullptr, &this->m_bucket);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::c_iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::cbegin(size_t buckidx)
{
	if (buckidx < this->m_bucket.size())
		return _GUnorderedSet_CIterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(this->m_bucket[buckidx], &this->m_bucket);
	return _GUnorderedSet_CIterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(nullptr, &this->m_bucket);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::c_iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::cend(size_t buckidx)
{
	if (buckidx < this->m_bucket.size()) {
		node_pointer p = this->m_bucket[buckidx];
		while (p->next != nullptr)p = p->next;
		return _GUnorderedSet_CIterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(p, &this->m_bucket);
	}
	return _GUnorderedSet_CIterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(nullptr, &this->m_bucket);
}

//特殊查找操作
//*******************************************************************************************************************************************************************************************************************

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline size_t GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::count(const T& val)
{
	return this->__countof(val);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline T& GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::find(const T& val)
{
	if (this->m_count == 0)
		return T();
	node_pointer res = this->__search(val);
	if (res == nullptr)
		return this->__first_node()->key;
	return res->key;
}

//虚函数重写
//*******************************************************************************************************************************************************************************************************************

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline bool GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::empty()
{
	return this->m_count == 0;
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline size_t GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::size()
{
	return this->m_count;
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline void GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::clear()
{
	this->__clear();
}

//运算符重写
//*******************************************************************************************************************************************************************************************************************

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline bool GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::operator==(const __GUnorderedSet& rhs)
{
	if (this->m_bucket.size() != rhs.m_bucket.size() || this->m_count != rhs.m_count)
		return false;
	for (int index = 0; index < this->m_bucket.size(); index++)
	{
		node_pointer p = this->m_bucket[index];
		node_pointer q=rhs.m_bucket[index];

		while (p != nullptr && q != nullptr)
		{
			if (p->key != q->key)
				return false;
		}

		if ((p == nullptr && q != nullptr) || (p != nullptr && q == nullptr))
			return false;
	}
	return true;
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline bool GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::operator!=(const __GUnorderedSet& rhs)
{
	return !(*this == rhs);
}



//迭代器
//*******************************************************************************************************************************************************************************************************************

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::begin()
{
	node_pointer p = this->__first_node();
	return _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(p, &this->m_bucket);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::end()
{
	return _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(nullptr, &this->m_bucket);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::c_iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::cbegin()
{
	node_pointer p = this->__first_node();
	return _GUnorderedSet_CIterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(p, &this->m_bucket);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::c_iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::cend()
{
	return _GUnorderedSet_CIterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(nullptr, &this->m_bucket);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::r_iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::rbegin()
{
	node_pointer p = this->__last_node();
	return _GUnorderedSet_RIterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(p, &this->m_bucket);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::r_iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::rend()
{
	return _GUnorderedSet_RIterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(nullptr, &this->m_bucket);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::cr_iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::crbegin()
{
	node_pointer p = this->__last_node();
	return _GUnorderedSet_CRIterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(p, &this->m_bucket);
}

template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti>
inline typename __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::cr_iterator_type GEngine::GStl::__GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, IsMulti>::crend()
{
	return _GUnorderedSet_CRIterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(nullptr, &this->m_bucket);
}