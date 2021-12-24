// 构造函数
//**********************************************************************************************************************************************

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
__GSet<T, IsMulti, Compare, MMFun>::__GSet() { }

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
__GSet<T, IsMulti, Compare, MMFun>::__GSet(const __GSet& cv)
{
	node_pointer cv_root = cv.m_root;
	node_pointer temp = this->__minimum(cv_root);
	while (temp != nullptr)
	{
		this->__insert(temp->key);
		temp = this->Successor(temp);
	}
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
__GSet<T, IsMulti, Compare, MMFun>::__GSet(__GSet&& rv) noexcept
{
	this->m_root = rv.m_root;
	this->m_count = rv.m_count;
	rv.m_root = nullptr;
	rv.m_count = 0;
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
__GSet<T, IsMulti, Compare, MMFun>::__GSet(iterator_type _begin, iterator_type _end)
{
	for (auto p = _begin; p != _end; p++)
		insert(*p);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
__GSet<T, IsMulti, Compare, MMFun>::__GSet(std::initializer_list<T> values)
{
	for (auto p = values.begin(); p != values.end(); p++)
		insert(*p);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
__GSet<T, IsMulti, Compare, MMFun>::~__GSet()
{
	this->Destroy();
}

//赋值函数
//**********************************************************************************************************************************************
template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void __GSet<T, IsMulti, Compare, MMFun>::operator=(const __GSet& cv)
{
	clear();
	node_pointer cv_root = cv.m_root;
	node_pointer cv_firste = this->__minimum(cv_root);
	iterator_type src_iter = _GSet_Iterator<T, Compare, MMFun>(cv_firste);
	iterator_type _end = _GSet_Iterator<T, Compare, MMFun>(nullptr);

	for (src_iter; src_iter != _end; src_iter++)
		insert(*src_iter);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void __GSet<T, IsMulti, Compare, MMFun>::operator=(__GSet&& rv) noexcept
{
	clear();
	this->m_root = rv.m_root;
	this->m_count = rv.m_count;
	rv.m_root = nullptr;
	rv.m_count = 0;
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void __GSet<T, IsMulti, Compare, MMFun>::operator=(std::initializer_list<T> values)
{
	clear();
	for (auto p = values.begin(); p != values.end(); p++)
	{
		insert(*p);
	}
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void __GSet<T, IsMulti, Compare, MMFun>::swap(__GSet& v)
{
	node_pointer temp = v.m_root;
	size_t temp_size = v.m_count;

	v.m_root = this->m_root;
	v.m_count = this->m_count;

	this->m_root = temp;
	this->m_count = temp_size;
}



template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
Compare __GSet<T, IsMulti, Compare, MMFun>::value_comparator()
{
	return this->comparator;
}

//安插和移除
//**********************************************************************************************************************************************

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
GPair<typename __GSet<T, IsMulti, Compare, MMFun>::iterator_type, bool> __GSet<T, IsMulti, Compare, MMFun>::insert(const T& val)
{
	if (IsMulti)
	{
		node_pointer node = this->__insert(val);
		return GPair<iterator_type, bool>(_GSet_Iterator<T, Compare, MMFun>(node), true);
	}
	else
	{
		node_pointer res = this->Search(val);
		if (res != nullptr)
			return GPair<iterator_type, bool>(res, false);
		node_pointer node = this->__insert(val);
		return GPair<iterator_type, bool>(_GSet_Iterator<T, Compare, MMFun>(node), true);
	}
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void __GSet<T, IsMulti, Compare, MMFun>::insert(iterator_type _begin, iterator_type _end)
{
	for (iterator_type p = _begin; p != _end; p++)
		insert(*p);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void __GSet<T, IsMulti, Compare, MMFun>::insert(std::initializer_list<T> values)
{
	for (auto p = values.begin(); p != values.end(); p++)
		insert(*p);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
template<typename... Args>
GPair<typename __GSet<T, IsMulti, Compare, MMFun>::iterator_type, bool> __GSet<T, IsMulti, Compare, MMFun>::emplace(Args... args)
{
	T val(args...);
	return insert(val);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void __GSet<T, IsMulti, Compare, MMFun>::earse(const T& val)
{
	if (IsMulti)
	{
		node_pointer res = this->Search(val);
		while (res != nullptr)
		{
			this->__remove(this->m_root,res);
			res = this->Search(val);
		}
	}
	else
	{
		this->Remove(val);
	}
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void __GSet<T, IsMulti, Compare, MMFun>::earse(iterator_type pos)
{
	node_pointer node = pos.current;
	if (node != nullptr) {
		this->__remove(this->m_root, node);
		pos.current = nullptr;
	}
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void __GSet<T, IsMulti, Compare, MMFun>::earse(iterator_type _begin, iterator_type _end)
{
	iterator_type p = _begin;
	while(p!=_end)
		this->__remove(this->m_root, (p++).current);
}


// 虚函数重写
//**********************************************************************************************************************************************

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool __GSet<T, IsMulti, Compare, MMFun>::empty() const
{
	return this->m_count == 0;
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
size_t __GSet<T, IsMulti, Compare, MMFun>::size() const
{
	return this->m_count;
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void __GSet<T, IsMulti, Compare, MMFun>::clear()
{
	this->Destroy();
}


//特殊的查找函数
//**********************************************************************************************************************************************

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
size_t __GSet<T, IsMulti, Compare, MMFun>::count(const T& val)
{
	if (IsMulti)
	{
		node_pointer res = this->Search(val);
		if (res == nullptr)
			return 0;
		size_t _count = 1;
		res = this->Successor(res);
		while (res != nullptr && res->key == val)
		{
			_count++;
			res = this->Successor(res);
		}
		return _count;
	}
	else
	{
		node_pointer res = this->Search(val);
		if (res == nullptr)
			return 0;
		else
			return 1;
	}
}


template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename __GSet<T, IsMulti, Compare, MMFun>::iterator_type __GSet<T, IsMulti, Compare, MMFun>::find(const T& val)
{
	node_pointer res= this->Search(val);
	return _GSet_Iterator<T, Compare, MMFun>(res);
}


// 运算符重载
//**********************************************************************************************************************************************

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool __GSet<T, IsMulti, Compare, MMFun>::operator==(const __GSet& rhs)
{
	if (rhs.m_count != this->m_count)
		return false;

	iterator_type lhs_iter = begin();
	node_pointer rhs_firste = this->__minimum(rhs.m_root);
	iterator_type rhs_iter = _GSet_Iterator<T, Compare, MMFun>(rhs_firste);
	iterator_type _end = _GSet_Iterator<T, Compare, MMFun>(nullptr);

	while (lhs_iter != _end && rhs_iter != _end)
	{
		if (*lhs_iter != *rhs_iter)
			return false;
		lhs_iter++;
		rhs_iter++;
	}
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool __GSet<T, IsMulti, Compare, MMFun>::operator!=(const __GSet& rhs)
{
	iterator_type lhs_iter = begin();
	node_pointer rhs_firste = this->__minimum(rhs.m_root);
	iterator_type rhs_iter = _GSet_Iterator<T, Compare, MMFun>(rhs_firste);
	iterator_type _end = _GSet_Iterator<T, Compare, MMFun>(nullptr);

	while (lhs_iter != _end && rhs_iter != _end)
	{
		if (*lhs_iter != *rhs_iter)
			return false;
		lhs_iter++;
		rhs_iter++;
	}

	return lhs_iter != _end || rhs_iter != _end;
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool __GSet<T, IsMulti, Compare, MMFun>::operator<(const __GSet& rhs)
{
	iterator_type lhs_iter = begin();
	node_pointer rhs_firste = this->__minimum(rhs.m_root);
	iterator_type rhs_iter = _GSet_Iterator<T, Compare, MMFun>(rhs_firste);
	iterator_type _end = _GSet_Iterator<T, Compare, MMFun>(nullptr);

	while (lhs_iter != _end && rhs_iter != _end)
	{
		if (*lhs_iter < *rhs_iter)
			return true;
		if ((*lhs_iter > *rhs_iter))
			return false;

		lhs_iter++;
		rhs_iter++;
	}

	return rhs_iter != _end;
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool __GSet<T, IsMulti, Compare, MMFun>::operator>(const __GSet& rhs)
{
	iterator_type lhs_iter = begin();
	node_pointer rhs_firste = this->__minimum(rhs.m_root);
	iterator_type rhs_iter = _GSet_Iterator<T, Compare, MMFun>(rhs_firste);
	iterator_type _end = _GSet_Iterator<T, Compare, MMFun>(nullptr);

	while (lhs_iter != _end && rhs_iter != _end)
	{
		if (*lhs_iter > *rhs_iter)
			return true;
		if ((*lhs_iter < *rhs_iter))
			return false;

		lhs_iter++;
		rhs_iter++;
	}

	return lhs_iter != _end;
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool __GSet<T, IsMulti, Compare, MMFun>::operator>=(const __GSet& rhs)
{
	return *this > rhs || *this == rhs;
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool __GSet<T, IsMulti, Compare, MMFun>::operator<=(const __GSet& rhs)
{
	return *this < rhs || *this == rhs;
}

// 迭代器相关函数
//**********************************************************************************************************************************************

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename __GSet<T, IsMulti, Compare, MMFun>::iterator_type __GSet<T, IsMulti, Compare, MMFun>::begin()
{
	node_pointer minmum = this->Minmum();
	return _GSet_Iterator<T, Compare, MMFun>(minmum);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename __GSet<T, IsMulti, Compare, MMFun>::iterator_type __GSet<T, IsMulti, Compare, MMFun>::end()
{
	return _GSet_Iterator<T, Compare, MMFun>(nullptr);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename __GSet<T, IsMulti, Compare, MMFun>::c_iterator_type __GSet<T, IsMulti, Compare, MMFun>::cbegin()
{
	node_pointer minmum = this->Minmum();
	return _GSet_CIterator<T, Compare, MMFun>(minmum);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename __GSet<T, IsMulti, Compare, MMFun>::c_iterator_type __GSet<T, IsMulti, Compare, MMFun>::cend()
{
	return _GSet_CIterator<T, Compare, MMFun>(nullptr);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename __GSet<T, IsMulti, Compare, MMFun>::r_iterator_type __GSet<T, IsMulti, Compare, MMFun>::rbegin()
{
	node_pointer maxmum = this->Maxmum();
	return _GSet_RIterator<T, Compare, MMFun>(maxmum);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename __GSet<T, IsMulti, Compare, MMFun>::r_iterator_type __GSet<T, IsMulti, Compare, MMFun>::rend()
{
	return _GSet_RIterator<T, Compare, MMFun>(nullptr);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename __GSet<T, IsMulti, Compare, MMFun>::cr_iterator_type __GSet<T, IsMulti, Compare, MMFun>::crbegin()
{
	node_pointer maxmum = this->Maxmum();
	return _GSet_CRIterator<T, Compare, MMFun>(maxmum);
}

template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename __GSet<T, IsMulti, Compare, MMFun>::cr_iterator_type __GSet<T, IsMulti, Compare, MMFun>::crend()
{
	return _GSet_CRIterator<T, Compare, MMFun>(nullptr);
}