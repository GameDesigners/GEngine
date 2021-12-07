// 构造函数
//*************************************************************************
template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::GList()
{
	m_head = nullptr;
	m_tail = nullptr;
	m_count = 0;
}

template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::GList(const GList& cv)
{
	if (cv.m_count == 0)
		return;

	m_head = nullptr;
	m_tail = nullptr;
	m_count = 0;

	node_pointer p = cv.m_head;
	while (true)
	{
		node_pointer temp = p->next;
		push_back(p->value);
		if (p == cv.m_tail)
			break;
		p = temp;
	}

}

template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::GList(GList&& rv)
{
	m_head = rv.m_head;
	m_tail = rv.m_tail;
	m_count = rv.m_count;

	rv.m_head = nullptr;
	rv.m_tail = nullptr;
	rv.m_count = 0;
}

template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::GList(size_t _count)
{
	GNEW(this)GList(_count, T());
}

template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::GList(size_t _count, const T& val)
{
	m_head = nullptr;
	m_tail = nullptr;
	m_count = 0;

	for (int index = 0; index < _count; index++)
		push_back(val);
}

template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::GList(iterator_type _begin, iterator_type _end)
{
	for (iterator_type p = _begin; p != _end; p++)
		push_back(p);
}

template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::GList(std::initializer_list<T> values)
{
	for (auto p = values.begin(); p != values.end(); p++)
		push_back(*p);
}

template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::~GList()
{
	if (m_count == 0)
		return;

	node_pointer p = m_head;
	while(true)
	{
		node_pointer temp = p->next;
		this->Delete(p, 1, 1);
		if (p == m_tail)
			break;
		p = temp;
	}
	m_head = m_tail = nullptr;
	m_count = 0;
}


// 赋值函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::operator=(const GList& cv)
{
	if (cv.m_count == 0)
		return;

	for (iterator_type q = cv.begin_iter; q != cv.end_iter; q++)
		push_back(*q); 
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::operator=(GList&& rv)
{
	m_head = rv.m_head;
	m_tail = rv.m_tail;
	m_count = rv.m_count;

	rv.m_head = nullptr;
	rv.m_tail = nullptr;
	rv.m_count = 0;
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::operator=(std::initializer_list<T> values)
{
	node_pointer elem = m_head;
	for (auto p = values.begin(); p != values.end(); p++)
	{
		if (elem != nullptr)
		{
			elem->value = *p;
			elem++;
		}
		else
			push_back(*p);
	}
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::assign(size_t _count, const T& val)
{
	node_pointer elem = m_head;
	for (int index = 0; index < _count; index++)
	{
		if (elem != nullptr)
		{
			elem->value = val;
			elem++;
		}
		else
			push_back(val);
	}
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::assign(iterator_type _begin, iterator_type _end)
{
	node_pointer elem = m_head;
	for (auto p = _begin; p != _end; p++)
	{
		if (elem != nullptr)
		{
			elem->value = *p;
			elem++;
		}
		else
			push_back(*p);
	}
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::assign(std::initializer_list<T> values)
{
	node_pointer elem = m_head;
	for (auto p = values.begin(); p != values.end(); p++)
	{
		if (elem != nullptr)
		{
			elem->value = *p;
			elem++;
		}
		else
			push_back(*p);
	}
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::swap(GList& list)
{
	node_pointer temp_head = m_head;
	node_pointer temp_tail = m_tail;
	size_t temp_count = m_count;

	m_head = list.m_head;
	m_tail = list.m_tail;
	m_count = list.m_count;

	list.m_head = temp_head;
	list.m_tail = temp_tail;
	list.m_count = temp_count;
}


//访问函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
T& GList<T, MMFun>::front()
{
	GASSERT(m_head != nullptr);
	return m_head->value;
}

template<class T, GMemManagerFun MMFun>
T& GList<T, MMFun>::back()
{
	GASSERT(m_tail != nullptr);
	return m_tail->value;
}


//访问函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::push_back(const T& val)
{
	node_pointer node = this->New(1);
	GASSERT(node != nullptr);
	construct(&node->value, val);
	if (m_count == 0 && m_head == nullptr && m_tail == nullptr)
	{
		m_head = m_tail = node;
		m_count = 1;
	}
	else
	{
		m_tail->next = node;
		node->prev = m_tail;
		m_tail = node;
		m_count++;
	}
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::pop_back()
{
	if (m_count == 0 && m_head == nullptr && m_tail == nullptr)
		return;

	node_pointer delete_node = m_tail;
	m_tail = m_tail->prev;
	m_tail->next = nullptr;
	this->Delete(delete_node, 1, 1);
	m_count--;
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::push_front(const T& val)
{
	node_pointer node = this->New(1);
	GASSERT(node != nullptr);
	construct(&node->value, val);
	if (m_count == 0 && m_head == nullptr && m_tail == nullptr)
	{
		m_head = m_tail = node;
		m_count = 1;
	}
	else
	{
		m_head->prev = node;
		node->next = m_head;
		m_head = node;
		m_count++;
	}
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::pop_front()
{
	if (m_count == 0 && m_head == nullptr && m_tail == nullptr)
		return;

	node_pointer delete_node = m_head;
	m_head = m_head->next;
	m_head->prev = nullptr;
	this->Delete(delete_node, 1, 1);
	m_count--;
}

template<class T, GMemManagerFun MMFun>
typename GList<T, MMFun>::iterator_type GList<T, MMFun>::insert(iterator_type pos, const T& val)
{
	if (pos == begin()) 
	{
		push_front(val);
		return begin();
	}
	else if (pos == end())
	{
		push_back(val);
		return end();
	}
	else
	{
		node_pointer node = this->New(1);
		GASSERT(node != nullptr);
		node->prev = pos.current->prev;
		node->next = pos.current;
		pos.current->prev->next = node;
		pos.current->prev = node;
		m_count++;
		return _List_Iterator<T>(node);
	}
}

template<class T, GMemManagerFun MMFun>
typename GList<T, MMFun>::iterator_type GList<T, MMFun>::insert(iterator_type pos, size_t _count, const T& val)
{
	if (_count == 0)
		return pos;

	if (pos == begin())
	{
		while (_count > 0) {
			push_front(val);
			_count--;
		}
		return begin();
	}
	else if (pos == end())
	{
		while (_count > 0) {
			push_back(val);
			_count--;
		}
		return end();
	}
	else
	{
		node_pointer first = this->New(1);
		GASSERT(first != nullptr);
		construct(&first->value, val);

		node_pointer last = first;
		while (_count > 0)
		{
			node_pointer node = this->New(1);
			GASSERT(node != nullptr);
			construct(&node->value, val);
			last->next = node;
			node->prev = last;
			last = node;
			_count--;
		}

		first->prev = pos.current->prev;
		pos.current->prev->next = first;
		last->next = pos.current;
		pos.current->prev = last;
		m_count += _count;
	}
}

template<class T, GMemManagerFun MMFun>
typename GList<T, MMFun>::iterator_type GList<T, MMFun>::insert(iterator_type pos, iterator_type _begin, iterator_type _end)
{
	if (pos == begin())
	{
		for (iterator_type p = _begin; p != _end; p++)
			push_front(*p);
		return begin();
	}
	else if (pos == end())
	{
		for (iterator_type p = _begin; p != _end; p++)
			push_back(*p);
		return end();
	}
	else
	{
		node_pointer first = this->New(1);
		GASSERT(first != nullptr);
		construct(&first->value, *_begin);
		m_count++;

		node_pointer last = first;
		for(iterator_type p=++_begin;p!=_end;p++)
		{
			node_pointer node = this->New(1);
			GASSERT(node != nullptr);
			construct(&node->value, *p);
			last->next = node;
			node->prev = last;
			last = node;
			m_count++;
		}

		first->prev = pos.current->prev;
		pos.current->prev->next = first;
		last->next = pos.current;
		pos.current->prev = last;
		return _List_Iterator<T, MMFun>(first);
	}
}

template<class T, GMemManagerFun MMFun>
typename GList<T, MMFun>::iterator_type GList<T, MMFun>::insert(iterator_type pos, std::initializer_list<T> values)
{
	if (values.size() == 0)
		return pos;

	if (pos == begin())
	{
		for (auto p = values.begin(); p != values.end(); p++)
			push_front(*p);
		return begin();
	}
	else if (pos == end())
	{
		for (auto p = values.begin(); p != values.end(); p++)
			push_back(*p);
		return end();
	}
	else
	{
		node_pointer first = this->New(1);
		GASSERT(first != nullptr);
		construct(&first->value, *(values.begin()));

		node_pointer last = first;
		for (auto p = values.begin(); p != values.end(); p++)
		{
			node_pointer node = this->New(1);
			GASSERT(node != nullptr);
			construct(&node->value, *p);
			last->next = node;
			node->prev = last;
			last = node;
			m_count++;
		}

		first->prev = pos.current->prev;
		pos.current->prev->next = first;
		last->next = pos.current;
		pos.current->prev = last;
		m_count += values.size();
		return _List_Iterator<T, MMFun>(first);
	}
}

template<class T, GMemManagerFun MMFun>
template<class ...Args>
typename GList<T, MMFun>::iterator_type GList<T, MMFun>::emplace(iterator_type pos, Args... args)
{
	return insert(pos, T(args...));
}

template<class T, GMemManagerFun MMFun>
template<class ...Args>
void GList<T, MMFun>::emplace_back(Args... args)
{
	push_back(T(args...));
}

template<class T, GMemManagerFun MMFun>
template<class ...Args>
void GList<T, MMFun>::emplace_front(Args... args)
{
	push_front(T(args...));
}

template<class T, GMemManagerFun MMFun>
typename GList<T, MMFun>::iterator_type GList<T, MMFun>::erase(iterator_type pos)
{
	if (m_count == 1 && m_head == m_tail)
	{
		this->Delete(pos.current, 1, 1);
		m_head = m_tail == nullptr;
		m_count = 0;
		return _List_Iterator<T, MMFun>(nullptr);
	}

	if (pos == begin())
	{
		pop_front();
		return begin();
	}
	else if (pos == end())
	{
		pop_back();
		return end();
	}
	else
	{
		node_pointer temp = pos.current->next;
		pos.current->prev->next = pos.current->next;
		pos.current->next->prev = pos.current->prev;
		this->Delete(pos.current, 1, 1);
		m_count--;
		return _List_Iterator<T, MMFun>(temp);
	}
}

template<class T, GMemManagerFun MMFun>
typename GList<T, MMFun>::iterator_type GList<T, MMFun>::erase(iterator_type _begin, iterator_type _end)
{
	bool is_begin = _begin == begin();
	bool is_end = _end == end();
	node_pointer return_node = nullptr;

	if (is_begin && is_end) 
	{
		clear();
		return _List_Iterator<T, MMFun>(nullptr);
	}
	else if (is_begin)
	{
		m_head = _end.current;
		return_node = m_head;
	}
	else if (is_end)
	{
		m_tail = _begin.current->prev;
		return_node = m_tail;
	}
	else
	{
		_begin.current->prev->next = _end.current;
		_end.current->prev = _begin.current->prev;
		return_node = _begin.current->prev;
	}

	while (_begin != _end)
	{
		iterator_type temp = _begin++;
		this->Delete(_begin, 1, 1);
		m_count--;
		_begin = temp;
	}
	return _List_Iterator<T, MMFun>(return_node);
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::remove(const T& val)
{
	remove_if(Equals(val));
}

template<class T, GMemManagerFun MMFun>
template<class OP> 
void GList<T, MMFun>::remove_if(OP op)
{
	if (m_count == 0)
		return;

	for (iterator_type p = begin(); p != end(); p++)
	{
		if (op(*p))
			erase(p);
	}
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::resize(size_t _count)
{

}


//访问函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
bool GList<T, MMFun>::empty()
{
	return m_count == 0;
}

template<class T, GMemManagerFun MMFun>
size_t GList<T, MMFun>::size()
{
	return m_count;
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::clear()
{
	node_pointer p = m_head;
	while (p != nullptr)
	{
		node_pointer temp = p->next;
		this->Delete(p, 1, 1);
		p = temp;
	}
	m_head = m_tail = nullptr;
	m_count = 0;
}


//访问函数
//*************************************************************************

template<class T, GMemManagerFun MMFun> 
bool GList<T, MMFun>::operator==(const GList& rhs)
{
	node_pointer p = m_head;
	node_pointer q = rhs.m_head;
	if (rhs.m_count != m_count)
		return false;

	while (p != nullptr && q != nullptr)
	{
		if (p->value != q->value)
			return false;
		p = p->next;
		q = q->next;
	}
	return true;
}

template<class T, GMemManagerFun MMFun>
bool GList<T, MMFun>::operator!=(const GList& rhs)
{
	return !(*this == rhs);
}

template<class T, GMemManagerFun MMFun>
bool GList<T, MMFun>::operator<(const GList& rhs)
{
	node_pointer p = m_head;
	node_pointer q = rhs.m_head;

	while (p != nullptr && q != nullptr)
	{
		if (p->value < q->value)
			return true;
		if (p->value > q->value)
			return false;
		p = p->next;
		q = q->next;
	}
	return p == nullptr && q != nullptr;
}

template<class T, GMemManagerFun MMFun>
bool GList<T, MMFun>::operator>(const GList& rhs)
{
	node_pointer p = m_head;
	node_pointer q = rhs.m_head;

	while (p != nullptr && q != nullptr)
	{
		if (p->value > q->value)
			return true;
		if (p->value < q->value)
			return false;
		p = p->next;
		q = q->next;
	}
	return p != nullptr && q == nullptr;
}

template<class T, GMemManagerFun MMFun>
bool GList<T, MMFun>::operator>=(const GList& rhs)
{
	node_pointer p = m_head;
	node_pointer q = rhs.m_head;

	while (p != nullptr && q != nullptr)
	{
		if (p->value > q->value)
			return true;
		if (p->value < q->value)
			return false;
		p = p->next;
		q = q->next;
	}
	return p == nullptr && q == nullptr;
}

template<class T, GMemManagerFun MMFun>
bool GList<T, MMFun>::operator<=(const GList& rhs)
{
	node_pointer p = m_head;
	node_pointer q = rhs.m_head;

	while (p != nullptr && q != nullptr)
	{
		if (p->value < q->value)
			return true;
		if (p->value > q->value)
			return false;
		p = p->next;
		q = q->next;
	}
	return p == nullptr && q == nullptr;
}


//迭代器函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
typename GList<T, MMFun>::iterator_type GList<T, MMFun>::begin()
{
	if (m_count == 0)
		return _List_Iterator<T, MMFun>(nullptr);
	return _List_Iterator<T, MMFun>(m_head);
}

template<class T, GMemManagerFun MMFun>
typename GList<T, MMFun>::iterator_type GList<T, MMFun>::end()
{
	if (m_count == 0)
		return _List_Iterator<T, MMFun>(nullptr);
	return _List_Iterator<T,MMFun>(m_tail->next);
}