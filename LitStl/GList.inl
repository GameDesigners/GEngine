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

	m_head = m_tail = __new_list_node(cv.m_head->value);
	node_pointer p = m_head;
	node_pointer q = cv.m_head->next;
	while (q!=nullptr)
	{
		node_pointer node = __new_list_node(q->value);
		p->next = node;
		node->prev = p;
		p = node;
		if (q == cv.m_tail)
			break;
		q = q->next;
	}
	m_tail = p;
	m_count = cv.m_count;
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
	m_head = nullptr;
	m_tail = nullptr;
	m_count = 0;
	assign(_count, T());
}

template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::GList(size_t _count, const T& val)
{
	m_head = nullptr;
	m_tail = nullptr;
	m_count = 0;
	assign(_count, val);
}

template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::GList(iterator_type _begin, iterator_type _end)
{
	m_head = nullptr;
	m_tail = nullptr;
	m_count = 0;
	assign(_begin, _end);
}

template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::GList(std::initializer_list<T> values)
{
	m_head = nullptr;
	m_tail = nullptr;
	m_count = 0;
	assign(values);
}

template<class T, GMemManagerFun MMFun>
GList<T, MMFun>::~GList()
{
	clear();	
}


// 赋值函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::operator=(const GList& cv)
{
	if (cv.m_count == 0)
		return;

	iterator_type _begin = _List_Iterator<T, MMFun>(cv.m_head);
	iterator_type _end = _List_Iterator<T, MMFun>(cv.m_tail->next);
	assign(_begin, _end);
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
	clear();
	if (values.size() == 0)
		return;

	for (auto p = values.begin(); p != values.end(); p++)
		push_back(*p);
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::assign(size_t _count, const T& val)
{
	if (_count == 0)
		clear();

	if (m_count == 0)
	{
		m_count = _count;
		m_head = m_tail = __new_list_node(val);
		_count--;
		node_pointer p = m_head;
		for (int index = 0; index < _count; index++)
		{
			node_pointer node = __new_list_node(val);
			p->next = node;
			node->prev = p;
			p = node;
		}
		m_tail = p;
		return;
	}
	else
	{
		//存在元素
		node_pointer p = m_head;
		size_t count = _count;
		for (int index = 0; index < m_count; index++) 
		{
			p->value = val;
			p = p->next;
			count--;
			if (count == 0)
				break;
		}

		if (m_count == count)
			return;

		if (count == 0) //需要删除后面的元素
		{
			m_tail = p->prev;
			__delete_after(p);
		}
		else
		{
			for (int index = 0; index < count; index++)
			{
				node_pointer node = __new_list_node(val);
				m_tail->next = node;
				node->prev = m_tail;
				m_tail = node;
			}
		}
	}
	m_count = _count;
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::assign(iterator_type _begin, iterator_type _end)
{
	if (m_count == 0)
	{
		node_pointer last = m_head;
		for (iterator_type p = _begin; p != _end; p++)
		{
			if (last ==nullptr)
				last = m_head = m_tail = __new_list_node(*p);
			else
			{
				node_pointer node = __new_list_node(*p);
				last->next = node;
				node->prev = last;
				last = node;
			}
			m_count++;
		}
		m_tail = last;
	}
	else
	{
		size_t temp_count = 0;
		node_pointer last = m_head;
		node_pointer prev = m_head;
		for (iterator_type p = _begin; p != _end; p++)
		{
			if (m_count != 0)
			{
				last->value = *p;
				prev = last;
				last = last->next;
				m_count--;
				temp_count++;
			}
			else
			{
				node_pointer node = __new_list_node(*p);
				prev->next = node;
				node->prev = prev;
				prev = node;
				temp_count++;
			}
		}

		m_tail = prev;
		m_count = temp_count;
	}
}

template<class T, GMemManagerFun MMFun>
void GList<T, MMFun>::assign(std::initializer_list<T> values)
{
	if (values.size() == 0)
		clear();

	if (m_count == 0)
	{
		auto q = values.begin();
		m_head = m_tail = __new_list_node(*q);
		m_count = 1;
		node_pointer p = m_head;
		for (++q;q!=values.end();q++)
		{
			node_pointer node = __new_list_node(*q);
			p->next = node;
			node->prev = p;
			p = node;
			m_count++;
		}
		m_tail = p;
		return;
	}

	clear();
	for (auto p = values.begin(); p != values.end(); p++)
		push_back(*p);
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
	if (m_count == 0)
		return;

	node_pointer p = m_head;
	while (true)
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