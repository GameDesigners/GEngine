// 构造函数
//*************************************************************************

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::GSet() {}

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::GSet(const GSet& cv)
{
	node_pointer temp = cv.m_root;
	while (temp != nullptr)
	{
		this->__insert(temp->key);
		temp = this->Successor(temp);
	}
}

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::GSet(GSet&& rv) noexcept
{
	this->m_root = rv.m_root;
	this->m_count = rv.m_count;
	rv.m_root = nullptr;
	rv.m_count = 0;
}

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::GSet(iterator_type _begin, iterator_type _end)
{
	for (auto p = _begin; p != _end; p++)
		this->__insert(*p);
}

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::GSet(std::initializer_list<T> values)
{
	for (auto p = values.begin(); p != values.end(); p++)
		this->__insert(*p);
}

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::~GSet()
{
	this->Destroy();
}

//赋值函数
//*************************************************************************
template<class T, typename Compare, GMemManagerFun MMFun>
void GSet<T, Compare, MMFun>::operator=(const GSet& cv)
{
	iterator_type cpy_node = begin();
	node_pointer cv_firste = this->__minimum(cv.m_root);
	iterator_type src_node = _GSet_Iterator<T, Compare, MMFun>(cv_firste);
	iterator_type _end = _GSet_Iterator<T, Compare, MMFun>(nullptr);

	while (cpy_node != _end || src_node != _end)
	{
		if (cpy_node != _end && src_node != _end)
		{
			cpy_node->key = src_node->key;
			cpy_node++;
			src_node++;
		}
		else if (cpy_node == _end && src_node != _end)
		{
			this->__insert(src_node->key);
			src_node++;
		}
		else
		{
			node_pointer temp = this->Successor(src_node->current);
			this->__remove(this->m_root, src_node->current);
			src_node.current = temp;
		}
	}
}

template<class T, typename Compare, GMemManagerFun MMFun>
void GSet<T, Compare, MMFun>::operator=(GSet&& rv) noexcept
{
	clear();
	this->m_root = rv.m_root;
	this->m_count = rv.m_count;
	rv.m_root = nullptr;
	rv.m_count = 0;
}

template<class T, typename Compare, GMemManagerFun MMFun>
void GSet<T, Compare, MMFun>::operator=(std::initializer_list<T> values)
{
	iterator_type q = begin();
	iterator_type _end = begin();
	for (auto p = values.begin(); p != values.end(); p++)
	{
		if (q != _end)
		{
			*q = *p;
			q++;
		}
		else
		{
			this->__insert(*p);
		}
	}

	while (q != _end)
	{
		node_pointer temp = this->Successor(q->current);
		this->__remove(this->m_root, q->current);
		q.current = temp;
	}
}

template<class T, typename Compare, GMemManagerFun MMFun>
void GSet<T, Compare, MMFun>::swap(GSet& v)
{
	node_pointer temp = v.m_root;
	size_t temp_size = v.m_count;

	v.m_root = this->m_root;
	v.m_count = this->m_count;

	this->m_root = temp;
	this->m_count = temp_size;
}



template<class T, typename Compare, GMemManagerFun MMFun>
Compare GSet<T, Compare, MMFun>::value_comparator()
{
	return this->comparator;
}

//安插和移除
//*************************************************************************

template<class T, typename Compare, GMemManagerFun MMFun>
void GSet<T, Compare, MMFun>::insert(const T& val)
{
	if (count(val) == 1)
		return;
	this->__insert(val);
}

template<class T, typename Compare, GMemManagerFun MMFun>
void GSet<T, Compare, MMFun>::insert(const iterator_type& pos, const T& val)
{
	this->__insert(pos->current, val);
}

template<class T, typename Compare, GMemManagerFun MMFun>
void GSet<T, Compare, MMFun>::insert(iterator_type _begin, iterator_type _end)
{
	for (iterator p = _begin; p != _end; p++)
		this->__insert(*p);
}

template<class T, typename Compare, GMemManagerFun MMFun>
template<typename... Args>
void GSet<T, Compare, MMFun>::emplace(Args... args)
{
	T val(args...);
	this->__insert(val);
}


// 虚函数重写
//*************************************************************************

template<class T, typename Compare, GMemManagerFun MMFun>
bool GSet<T, Compare, MMFun>::empty()
{
	return this->m_count == 0;
}

template<class T, typename Compare, GMemManagerFun MMFun>
size_t GSet<T, Compare, MMFun>::size()
{
	return this->m_count;
}

template<class T, typename Compare, GMemManagerFun MMFun>
void GSet<T, Compare, MMFun>::clear()
{
	this->Destroy();
}

// 迭代器相关函数
//*************************************************************************

template<class T, typename Compare, GMemManagerFun MMFun>
typename GSet<T, Compare, MMFun>::iterator_type GSet<T, Compare, MMFun>::begin()
{
	node_pointer minmum = this->Minmum();
	return _GSet_Iterator<T, Compare, MMFun>(minmum);
}

template<class T, typename Compare, GMemManagerFun MMFun>
typename GSet<T, Compare, MMFun>::iterator_type GSet<T, Compare, MMFun>::end()
{
	return _GSet_Iterator<T, Compare, MMFun>(nullptr);
}

template<class T, typename Compare, GMemManagerFun MMFun>
typename GSet<T, Compare, MMFun>::c_iterator_type GSet<T, Compare, MMFun>::cbegin()
{
	node_pointer minmum = this->Minmum();
	return _GSet_CIterator<T, Compare, MMFun>(minmum);
}

template<class T, typename Compare, GMemManagerFun MMFun>
typename GSet<T, Compare, MMFun>::c_iterator_type GSet<T, Compare, MMFun>::cend()
{
	return _GSet_CIterator<T, Compare, MMFun>(nullptr);
}

template<class T, typename Compare, GMemManagerFun MMFun>
typename GSet<T, Compare, MMFun>::r_iterator_type GSet<T, Compare, MMFun>::rbegin()
{
	node_pointer maxmum = this->Maxmum();
	return _GSet_RIterator<T, Compare, MMFun>(maxmum);
}

template<class T, typename Compare, GMemManagerFun MMFun>
typename GSet<T, Compare, MMFun>::r_iterator_type GSet<T, Compare, MMFun>::rend()
{
	return _GSet_RIterator<T, Compare, MMFun>(nullptr);
}

template<class T, typename Compare, GMemManagerFun MMFun>
typename GSet<T, Compare, MMFun>::cr_iterator_type GSet<T, Compare, MMFun>::crbegin()
{
	node_pointer maxmum = this->Maxmum();
	return _GSet_CRIterator<T, Compare, MMFun>(maxmum);
}

template<class T, typename Compare, GMemManagerFun MMFun>
typename GSet<T, Compare, MMFun>::cr_iterator_type GSet<T, Compare, MMFun>::crend()
{
	return _GSet_CRIterator<T, Compare, MMFun>(nullptr);
}