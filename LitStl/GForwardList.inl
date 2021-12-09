template<class T, GMemManagerFun MMFun>
GForwardList<T, MMFun>::GForwardList()
{
	m_head = nullptr;
}

template<class T, GMemManagerFun MMFun>
GForwardList<T, MMFun>::GForwardList(const GForwardList& cv)
{
	if (cv.m_head == nullptr)
		return;

	m_head = nullptr;
	node_pointer p = cv.m_head;
	node_pointer q = m_head = __new_forwardlist_node(p->value);
	p = p->next;
	while (p != nullptr)
	{
		node_pointer node = __new_forwardlist_node(p->value);
		q->next = node;
		q = node;
		p = p->next;
	}
	q->next = nullptr;
}

template<class T, GMemManagerFun MMFun>
GForwardList<T, MMFun>::GForwardList(GForwardList&& rv)
{
	m_head = rv.m_head;
	rv.m_head = nullptr;
}

template<class T, GMemManagerFun MMFun>
GForwardList<T, MMFun>::GForwardList(size_t _count)
{
	assign(_count, T());
}

template<class T, GMemManagerFun MMFun>
GForwardList<T, MMFun>::GForwardList(size_t _count, const T& val)
{
	assign(_count, val);
}

template<class T, GMemManagerFun MMFun>
GForwardList<T, MMFun>::GForwardList(iterator_type _begin, iterator_type _end)
{
	assign(_begin, _end);
}

template<class T, GMemManagerFun MMFun>
GForwardList<T, MMFun>::GForwardList(std::initializer_list<T> values)
{
	assign(values);
}

template<class T, GMemManagerFun MMFun>
GForwardList<T, MMFun>::~GForwardList()
{
	clear();
}

// 赋值函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::operator=(const GForwardList& cv)
{
	if (m_head == nullptr) 
	{
		node_pointer p = cv.m_head;
		node_pointer last = m_head;
		while (p != nullptr)
		{
			node_pointer node = this->New(1);
			GASSERT(node != nullptr);
			construct(&node->value, p->value);
			if (last == nullptr)
				m_head = last = node;
			else
			{
				last->next = node;
				last = node;
			}
		}
	}
	else
	{
		node_pointer p = cv.m_head;
		node_pointer q = m_head;
		node_pointer tail = m_head;
		while (p != nullptr && q != nullptr)
		{
			q->value = p->value;
			tail = q;
			
			p = p->next;
			q = q->next;
		}

		if (p == nullptr && q == nullptr)
			return;
		else
		{
			if (p == nullptr)//需要删除
				delete_after(q);
			else
			{
				while (p != nullptr)
				{
					node_pointer node = __new_forwardlist_node(p->value);
					tail->next = node;
					tail = node;
					p = p->next;
				}
			}
			tail->next = nullptr;
		}
	}
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::operator=(GForwardList&& rv)
{
	clear();
	m_head = rv.m_head;
	rv.m_head = nullptr;
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::operator=(std::initializer_list<T> values)
{
	assign(values);
}

template<class T,GMemManagerFun MMFun>
void GForwardList<T, MMFun>::assign(std::initializer_list<T> values)
{
	if (m_head == nullptr) 
	{
		node_pointer last = nullptr;
		for (auto p = values.begin(); p != values.end(); p++)
		{
			node_pointer node = this->New(1);
			GASSERT(node != nullptr);
			construct(&node->value, *p);
			if (last == nullptr)
				m_head = last = node;
			else
			{
				last->next = node;
				last = node;
			}
		}
		last->next = nullptr;
	}
	else
	{
		auto p = values.begin();
		node_pointer q = m_head;
		node_pointer tail = m_head;

		for (p; p != values.end(); p++)
		{
			q->value = *p;
			tail = q;
			q = q->next;
			if (q == nullptr)
				break;
		}

		if (p == values.end() && q == nullptr)
			return;
		else
		{
			if (p == values.end())//需要删除
				delete_after(q);
			else
			{
				while (p != values.end())
				{
					node_pointer node = __new_forwardlist_node(*p);
					tail->next = node;
					tail = node;
					p++;
				}
			}
		}
		tail->next = nullptr;
	}
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::assign(size_t _count, const T& val)
{
	if (_count == 0)
	{
		clear();
		return;
	}

	//非清理版本(减少重复构造)
	if (m_head == nullptr)
	{
		node_pointer last = m_head = __new_forwardlist_node(val);
		_count--;
		for (int index = 0; index < _count; index++)
		{
			node_pointer node = __new_forwardlist_node(val);
			last->next = node;
			last = node;
		}
		last->next = nullptr;
	}
	else
	{
		node_pointer last = m_head;
		node_pointer tail = m_head;
		while (_count != 0 && last != nullptr)
		{
			last->value = val;
			tail = last;
			last = last->next;
			_count--;
		}

		if (_count == 0 && last == nullptr)
			return;
		else if (_count == 0)
			delete_after(last);
		else if(_count!=0)
		{
			for (int index = 0; index < _count; index++)
			{
				node_pointer node = __new_forwardlist_node(val);
				tail->next = node;
				tail = node;
			}
		}	
		tail->next = nullptr;
	}

}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::assign(iterator_type _begin, iterator_type _end)
{
	if (m_head == nullptr) 
	{
		node_pointer last = nullptr;
		for (iterator_type p = _begin; p != _end; p++)
		{
			node_pointer node = this->New(1);
			GASSERT(node != nullptr);
			construct(&node->value, *p);
			if (last == nullptr)
				m_head = last = node;
			else
			{
				last->next = node;
				last = node;
			}
		}
		last->next = nullptr;
	}
	else
	{
		iterator_type p = _begin;
		node_pointer q = m_head;
		node_pointer tail = m_head;

		for (p; p != _end; p++)
		{
			q->value = *p;
			tail = q;
			q = q->next;
			if (q == nullptr)
				break;
		}

		if (p == _end && q == nullptr)
			return;
		else
		{
			if (p == _end)//需要删除
				delete_after(q);
			else
			{
				while (p != _end)
				{
					node_pointer node = __new_forwardlist_node(*p);
					tail->next = node;
					tail = node;
					p++;
				}
			}
		}
		tail->next = nullptr;
	}
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::swap(GForwardList& forward_list)
{
	node_pointer temp = m_head;
	m_head = forward_list.m_head;
	forward_list.m_head = temp;
}

// 赋值函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
T& GForwardList<T, MMFun>::front()
{
	return m_head->value;
}


// 赋值函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::push_front(const T& val)
{
	node_pointer node = this->New(1);
	GASSERT(node != nullptr);
	construct(&node->value, val);

	if (m_head == nullptr) {
		m_head = node;
		node->next = nullptr;
	}
	else
	{
		node->next = m_head;
		m_head = node;
	}
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::pop_front()
{
	if (m_head == nullptr)
		return;
	node_pointer delete_node = m_head;
	m_head = m_head->next;
	this->Delete(delete_node, 1, 1);
}

template<class T, GMemManagerFun MMFun>
typename typename GForwardList<T, MMFun>::iterator_type GForwardList<T, MMFun>::insert_after(iterator_type pos, const T& val)
{
	node_pointer node = __new_forwardlist_node(val);
	node->next = pos.current->next;
	pos.current->next = node;

	return _Forward_List_Iterator<T, MMFun>(node);
}

template<class T, GMemManagerFun MMFun>
typename GForwardList<T, MMFun>::iterator_type GForwardList<T, MMFun>::insert_after(iterator_type pos, size_t _count, const T& val)
{
	if (_count == 0)
		return pos;
	else if (_count == 1)
		return insert_after(pos, 1, val);
	else
	{
		node_pointer first = __new_forwardlist_node(val);
		node_pointer last = first;
		for (int index = 1; index < _count; index++)
		{
			node_pointer node = __new_forwardlist_node(val);
			last->next = node;
			last = node;
		}

		last->next = pos.current->next;
		pos.current->next = first;

		return _Forward_List_Iterator<T, MMFun>(first);
	}
}

template<class T, GMemManagerFun MMFun>
typename GForwardList<T, MMFun>::iterator_type GForwardList<T, MMFun>::insert_after(iterator_type pos, iterator_type _begin, iterator_type _end)
{
	node_pointer first = nullptr;
	node_pointer last = nullptr;

	for (iterator_type p = _begin; p != _end; p++)
	{
		node_pointer node = __new_forwardlist_node(*p);
		if (first == nullptr)
		{
			first = node;
			last = first;
		}
		else
		{
			last->next = node;
			last = node;
		}
	}
	
	if (first != nullptr)
	{
		last->next = pos.current->next;
		pos.current->next = first;

		return _Forward_List_Iterator<T, MMFun>(first);
	}
	else
		return pos;
}

template<class T, GMemManagerFun MMFun>
typename GForwardList<T, MMFun>::iterator_type GForwardList<T, MMFun>::insert_after(iterator_type pos, std::initializer_list<T> values)
{
	if (values.size() == 0)
		return pos;
	else if(values.size()==1)
		return insert_after(pos, 1, *values.begin());
	else
	{
		auto p = values.begin();
		node_pointer first = __new_forwardlist_node(*p);
		node_pointer last = first;
		p++;

		for (p;p!= values.end();p++)
		{
			node_pointer node = __new_forwardlist_node(*p);
			last->next = node;
			last = node;
		}

		last->next = pos.current->next;
		pos.current->next = first;

		return _Forward_List_Iterator<T, MMFun>(first);
	}
}

template<class T, GMemManagerFun MMFun>
template<class ...Args>
void GForwardList<T, MMFun>::emplace_after(iterator_type pos, Args ...args)
{
	T temp(args...);
	insert_after(pos, temp);
}

template<class T, GMemManagerFun MMFun>
template<class ...Args>
void GForwardList<T, MMFun>::emplace_front(Args ...args)
{
	T temp(args...);
	push_front(temp);
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::erase_after(iterator_type pos)
{
	node_pointer p = pos.current->next;
	for (p; p != nullptr; p++)
	{
		node_pointer temp = p->next;
		this->Delete(p, 1, 1);
		p = temp;
	}
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::erase_after(iterator_type _begin, iterator_type _end)
{
	if (_end == end())
	{
		erase_after(_begin);
		return;
	}


	node_pointer prev = m_head;
	while (prev->next != _begin.current && prev != nullptr)
		prev = prev->next;

	prev->next = _end.current;

	//删除
	node_pointer first = _begin.current;
	node_pointer last = _end.current;

	while (first != last && first != nullptr)
	{
		node_pointer temp = first->next;
		this->Delete(first, 1, 1);
		first = temp;
	}
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::remove(const T& val)
{
	Equals equals(val);
	remove_if(equals);
}

template<class T, GMemManagerFun MMFun>
template<class Operator>
void GForwardList<T, MMFun>::remove_if(Operator op)
{
	node_pointer p = m_head;
	node_pointer prev = m_head;
	while (p != nullptr)
	{
		node_pointer temp = p->next;
		if (op(p->value))
		{
			prev->next = p->next;
			this->Delete(p, 1, 1);
		}
		else
			prev = p;
		p = temp;
	}
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::resize(size_t _count)
{
	resize(_count, T());
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::resize(size_t _count, const T& cv)
{
	if (m_head == nullptr)
	{
		assign(_count, cv);
		return;
	}

	node_pointer p = m_head;
	for (int index = 1; index < _count; index++)
	{
		if (p == nullptr)
		{
			node_pointer node = this->New(1);
			GASSERT(node != nullptr);
			construct(&node->value, *p);

			p = node->next;
		}
		else
		{
			p = p->next;
		}
	}
	erase_after(_Forward_List_Iterator<T, MMFun>(p));
}

//特殊更易型操作
//*************************************************************************
template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::unique()
{
	Equals equals;
	unique(equals);
}

template<class T, GMemManagerFun MMFun>
template<class Operator>
void GForwardList<T, MMFun>::unique(Operator op)
{
	if (m_head->next == nullptr || m_head==nullptr)
		return;

	node_pointer p = m_head;
	while (p != nullptr && p->next == nullptr)
	{
		if (op(p->value, p->next->value))
		{
			node_pointer delete_node = p->next;
			p->next = p->next->next;
			this->Delete(delete_node, 1, 1);
		}
		else
		{
			p = p->next;
		}
	}
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::splice_after(iterator_type pos, GForwardList& v)
{
	if (v.m_head == nullptr || pos==end())
		return;

	if (pos.current == nullptr && m_head == nullptr) //容器为空
	{
		m_head = v.m_head;
		v.m_head = nullptr;
		return;
	}

	node_pointer last = v.m_head;
	while (last->next != nullptr&&last!=nullptr)
		last = last->next;

	last->next = pos.current->next;
	pos.current->next = v.m_head;
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::splice_after(iterator_type pos, GForwardList& v, iterator_type splice_target)
{
	if (v.m_head == nullptr || splice_target.current == nullptr || pos==end())
		return;

	node_pointer p = v.m_head;
	node_pointer target = splice_target.current;
	while (p->next != target && p != nullptr)
		p = p->next;

	//从v中移除目标节点
	p->next = target->next;

	if (v.m_head == nullptr && pos.current == nullptr)
		m_head = target;
	target->next = pos.current->next;
	pos.current->next = target;

}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::splice_after(iterator_type pos, GForwardList& v, iterator_type _begin, iterator_type _end)
{

}

// 虚函数重写
//*************************************************************************

template<class T, GMemManagerFun MMFun>
bool GForwardList<T, MMFun>::empty()
{
	return m_head == nullptr;
}

template<class T, GMemManagerFun MMFun>
void GForwardList<T, MMFun>::clear()
{
	node_pointer p = m_head;
	while (p != nullptr)
	{
		node_pointer temp = p->next;
		this->Delete(p, 1, 1);
		p = temp;
	}
}

//运算符重载
//*************************************************************************

template<class T, GMemManagerFun MMFun>
bool GForwardList<T, MMFun>::operator==(const GForwardList& rhs)
{
	node_pointer p = m_head;
	node_pointer q = rhs.m_head;

	while (p != nullptr && q != nullptr)
	{
		if (p->value != q->value)
			return false;
		p = p->next;
		q = q->next;
	}
	return p == nullptr && q == nullptr;
}

template<class T, GMemManagerFun MMFun>
bool GForwardList<T, MMFun>::operator!=(const GForwardList& rhs)
{
	node_pointer p = m_head;
	node_pointer q = rhs.m_head;

	while (p != nullptr && q != nullptr)
	{
		if (p->value != q->value)
			return true;
		p = p->next;
		q = q->next;
	}
	return p != nullptr || q != nullptr;
}

template<class T, GMemManagerFun MMFun>
bool GForwardList<T, MMFun>::operator<(const GForwardList& rhs)
{
	node_pointer p = m_head;
	node_pointer q = rhs.m_head;

	while (p != nullptr && q != nullptr)
	{
		if (p->value < q->value)
			return true;
		else if (p->value > q->value)
			return false;
		p = p->next;
		q = q->next;
	}
	return q != nullptr;
}

template<class T, GMemManagerFun MMFun>
bool GForwardList<T, MMFun>::operator>(const GForwardList& rhs)
{
	node_pointer p = m_head;
	node_pointer q = rhs.m_head;

	while (p != nullptr && q != nullptr)
	{
		if (p->value > q->value)
			return true;
		else if (p->value < q->value)
			return false;
		p = p->next;
		q = q->next;
	}
	return p != nullptr;
}

template<class T, GMemManagerFun MMFun>
bool GForwardList<T, MMFun>::operator>=(const GForwardList& rhs)
{
	node_pointer p = m_head;
	node_pointer q = rhs.m_head;

	while (p != nullptr && q != nullptr)
	{
		if (p->value > q->value)
			return true;
		else if (p->value < q->value)
			return false;
		p = p->next;
		q = q->next;
	}
	return q == nullptr;
}

template<class T, GMemManagerFun MMFun>
bool GForwardList<T, MMFun>::operator<=(const GForwardList& rhs)
{
	node_pointer p = m_head;
	node_pointer q = rhs.m_head;

	while (p != nullptr && q != nullptr)
	{
		if (p->value < q->value)
			return true;
		else if (p->value > q->value)
			return false;
		p = p->next;
		q = q->next;
	}
	return p == nullptr;
}


// 迭代器相关函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
typename GForwardList<T, MMFun>::iterator_type GForwardList<T, MMFun>::begin()
{
	return _Forward_List_Iterator<T, MMFun>(m_head);
}

template<class T, GMemManagerFun MMFun>
typename GForwardList<T, MMFun>::iterator_type GForwardList<T, MMFun>::end()
{
	return _Forward_List_Iterator<T, MMFun>(nullptr);
}

template<class T, GMemManagerFun MMFun>
typename GForwardList<T, MMFun>::c_iterator_type GForwardList<T, MMFun>::cbegin()
{
	return _Forward_List_CIterator<T, MMFun>(m_head);
}

template<class T, GMemManagerFun MMFun>
typename GForwardList<T, MMFun>::c_iterator_type GForwardList<T, MMFun>::cend()
{
	return _Forward_List_CIterator<T, MMFun>(nullptr);
}

