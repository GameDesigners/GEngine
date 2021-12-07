template<class T, GMemManagerFun MMFun>
__deque_memory_buffer_block<T, MMFun>::__deque_memory_buffer_block(size_t block_size)
{
	m_data = this->New(block_size);
	GASSERT(m_data != nullptr);
	m_count = 0;
	m_capcity = block_size;
	m_constructed = 0;
}

template<class T, GMemManagerFun MMFun>
__deque_memory_buffer_block<T, MMFun>::__deque_memory_buffer_block(const __deque_memory_buffer_block& cv)
{
	m_capcity = cv.m_capcity;
	m_count = cv.m_count;
	m_constructed = 0;
	for (int index = 0; index < cv.m_count; index++)
		_construct_idx(index, *(cv.m_data + index));
}

template<class T, GMemManagerFun MMFun>
__deque_memory_buffer_block<T, MMFun>::__deque_memory_buffer_block(__deque_memory_buffer_block&& rv)
{
	m_data = rv.m_data;
	m_count = rv.m_count;
	m_capcity = rv.m_capcity;
	m_constructed = rv.m_constructed;

	rv.m_data = nullptr;
	rv.m_count = 0;
	rv.m_capcity = 0;
	rv.m_constructed = 0;
}

template<class T, GMemManagerFun MMFun>
__deque_memory_buffer_block<T, MMFun>::~__deque_memory_buffer_block()
{
	if (m_data != nullptr)
	{
		this->Delete(m_data, m_capcity, m_constructed);
		m_data = nullptr;
		m_count = 0;
		m_capcity = 0;
		m_constructed = 0;
	}
}

template<class T, GMemManagerFun MMFun>
void __deque_memory_buffer_block<T, MMFun>::assign(size_t _count)
{
	for (int index = 0; index < _count && index < m_capcity; index++)
		_construct_no_cv(index);
	m_count = _count;
}

template<class T, GMemManagerFun MMFun>
void __deque_memory_buffer_block<T, MMFun>::assign(size_t _count, const T& val)
{
	GASSERT(m_data != nullptr);
	for (int index = 0; index < _count && index < m_capcity; index++)
		_construct_idx(index, val);
	m_count = _count;
}

template<class T, GMemManagerFun MMFun>
void __deque_memory_buffer_block<T, MMFun>::operator= (const __deque_memory_buffer_block& cv)
{
	for (int index = 0; index < cv.m_count && index < m_capcity; index++)
		_construct_idx(index, *(cv.m_data + index));
	m_count = cv.m_count;
}

template<class T, GMemManagerFun MMFun>
void __deque_memory_buffer_block<T, MMFun>::operator= (__deque_memory_buffer_block&& rv)
{
	if (m_data != nullptr)
	{
		this->Delete(m_data, m_capcity, m_constructed);
		m_data = nullptr;
		m_count = 0;
		m_capcity = 0;
		m_constructed = 0;
	}

	m_data = rv.m_data;
	m_count = rv.m_count;
	m_capcity = rv.m_capcity;
	m_constructed = rv.m_constructed;

	rv.m_data = nullptr;
	rv.m_count = 0;
	rv.m_capcity = 0;
	rv.m_constructed = 0;
}


template<class T, GMemManagerFun MMFun>
_Deque_Iterator<T> __deque_memory_buffer_block<T, MMFun>::insert(_iterator_type pos, const T& cv)
{
	if (full())  //满了
		return pos;
	if (!_vertify_iterator(pos))  //检验迭代器的合法性
		return pos;

	_construct_no_cv(m_count);    //新构造一个对象
	T* p = m_data + m_count;
	for (p; p - 1 != pos.current; p--)
		*p = *(p - 1);

	*p = cv;
	m_count++;
	return _Deque_Iterator<T, MMFun>(p, m_data, m_data + m_count, pos._node);
}

template<class T, GMemManagerFun MMFun>
void __deque_memory_buffer_block<T, MMFun>::push_back()
{
	_construct_idx(m_count);
	m_count++;
}


template<class T, GMemManagerFun MMFun>
void __deque_memory_buffer_block<T, MMFun>::remove(_iterator_type pos)
{
	if (empty())
		return pos;
	if (!_vertify_iterator(pos))
		return pos;

	T* p = pos.current;
	for (p; p != m_data + m_count; p++)
		*p = *(p + 1);
	_destruct_idx(m_count);
	m_count--;
}

template<class T, GMemManagerFun MMFun>
bool __deque_memory_buffer_block<T, MMFun>::full()
{
	return m_count == m_capcity;
}

template<class T, GMemManagerFun MMFun>
bool __deque_memory_buffer_block<T, MMFun>::empty()
{
	return m_count == 0;
}

template<class T, GMemManagerFun MMFun>
size_t __deque_memory_buffer_block<T, MMFun>::size()
{
	return m_count;
}

template<class T, GMemManagerFun MMFun>
size_t __deque_memory_buffer_block<T, MMFun>::capcity()
{
	return m_capcity;
}

template<class T, GMemManagerFun MMFun>
void __deque_memory_buffer_block<T, MMFun>::clear()
{
	if (ValueBase<T>::NeedsDestructor)
		while (m_constructed > 0)
			_destruct_idx(m_constructed - 1);
	m_count = 0;
}


//构造函数 
//*************************************************************************

template<class T, GMemManagerFun MMFun>
GDeque<T, MMFun>::GDeque()
{
	m_map = this->New(DefaultMapSize);
	GASSERT(m_map != nullptr);
	m_map_count = 0;
	m_map_capcity = 0;
}

template<class T, GMemManagerFun MMFun>
GDeque<T, MMFun>::GDeque(const GDeque& cv)
{
	m_map_capcity = cv.m_map_capcity;
	m_map = this->New(m_map_capcity);
	GASSERT(m_map != nullptr);

	for (int index = 0; index < m_map_capcity; index++)
	{
		_create_new_buffer_block(index);
		*m_map[index] = *(cv.m_map[index]);
	}
}

template<class T, GMemManagerFun MMFun>
GDeque<T, MMFun>::GDeque(GDeque&& rv)
{
	m_map = rv.m_map;
	m_map_count = rv.m_map_count;
	m_map_capcity = rv.m_map_capcity;

	rv.m_map = nullptr;
	rv.m_map_count = 0;
	rv.m_map_capcity = 0;
}

template<class T, GMemManagerFun MMFun>
GDeque<T, MMFun>::GDeque(size_t _count)
{
	m_map_capcity = _count / DefaultBufferSize == 0 ? 1 : (_count % DefaultBufferSize == 0 ? _count / DefaultBufferSize : _count / DefaultBufferSize + 1);
	m_map = this->New(m_map_capcity);
	GASSERT(m_map != nullptr);

	for (int index = 0; index < m_map_capcity; index++) 
	{
		_create_new_buffer_block(index);
		if (_count >= DefaultBufferSize)
			m_map[index]->assign(DefaultBufferSize);
		else
			m_map[index]->assign(_count);
		_count -= DefaultBufferSize;
	}
}

template<class T, GMemManagerFun MMFun>
GDeque<T, MMFun>::GDeque(size_t _count, const T& val)
{
	m_map_capcity = _count / DefaultBufferSize == 0 ? 1 : (_count % DefaultBufferSize == 0 ? _count / DefaultBufferSize : _count / DefaultBufferSize + 1);
	m_map = this->New(m_map_capcity);
	GASSERT(m_map != nullptr);
	for (int index = 0; index < m_map_capcity; index++)
	{
		_create_new_buffer_block(index);
		if (_count >= DefaultBufferSize)
			m_map[index]->assign(DefaultBufferSize, val);
		else
			m_map[index]->assign(_count, val);
		_count -= DefaultBufferSize;
	}
}

template<class T, GMemManagerFun MMFun>
GDeque<T, MMFun>::GDeque(std::initializer_list<T> values)
{
	size_t _count = values.size();
	m_map_capcity = _count / DefaultBufferSize == 0 ? 1 : (_count % DefaultBufferSize == 0 ? _count / DefaultBufferSize : _count / DefaultBufferSize + 1);
	m_map = this->New(m_map_capcity);
	T* p = (T*)values.begin();
	for (int i = 0; i < m_map_capcity; i++)
	{
		_create_new_buffer_block(i);
		for (int j = 0; j < DefaultBufferSize; j++) 
		{
			//直接操作构造以提高效率
			m_map[i]->_construct_idx(j, *p);
			m_map[i]->m_count++;
			p++;
			if (p == values.end())
				break;
		}
	}
}

template<class T, GMemManagerFun MMFun>
GDeque<T, MMFun>::~GDeque()
{
	//析构map指向的缓冲块
	for (int index = 0; index < m_map_count; index++)
		GSAFE_DELETE(m_map[index]);

	//释放map
	this->Delete(m_map, m_map_capcity, 0);
}


// 赋值函数
//*************************************************************************
template<class T, GMemManagerFun MMFun>
void GDeque<T, MMFun>::operator=(const GDeque& cv)
{
	if (m_map_count < cv.m_map_count)
	{
		for (int index = m_map_count; index < cv.m_map_count; index++)
			_create_new_buffer_block(index);
	}

	for (int index = 0; index < m_map_count; index++)
		*m_map[index] = *cv.m_map[index];
}

template<class T,GMemManagerFun MMFun>
void GDeque<T, MMFun>::operator=(GDeque&& rv)
{
	for (int index = 0; index < m_map_count; index++)
		GSAFE_DELETE(m_map[index]);
	this->Delete(m_map, m_map_capcity, 0);

	m_map = rv.m_map;
	m_map_count = rv.m_map_count;
	m_map_capcity = rv.m_map_capcity;

	rv.m_map = nullptr;
	rv.m_map_count = 0;
	rv.m_map_capcity = 0;
}

template<class T, GMemManagerFun MMFun>
void GDeque<T, MMFun>::operator=(std::initializer_list<T> values)
{
	clear();
	size_t _count = values.size();
	size_t target_capcity = _count / DefaultBufferSize == 0 ? 1 : (_count % DefaultBufferSize == 0 ? _count / DefaultBufferSize : _count / DefaultBufferSize + 1);
	T* p = (T*)values.begin();
	for (int i = 0; i < target_capcity; i++)
	{
		_create_new_buffer_block(i);
		for (int j = 0; j < DefaultBufferSize; j++)
		{
			//直接操作构造以提高效率
			m_map[i]->_construct_idx(j, *p);
			m_map[i]->m_count++;
			p++;
			if (p == values.end())
				break;
		}
	}
}

template<class T, GMemManagerFun MMFun>
void GDeque<T, MMFun>::assign(size_t _count, const T& val)
{
	clear();
	size_t target_capcity = _count / DefaultBufferSize == 0 ? 1 : (_count % DefaultBufferSize == 0 ? _count / DefaultBufferSize : _count / DefaultBufferSize + 1);
	for (int index = 0; index < target_capcity; index++)
	{
		_create_new_buffer_block(index);
		if (_count >= DefaultBufferSize)
			m_map[index]->assign(DefaultBufferSize, val);
		else
			m_map[index]->assign(_count, val);
		_count -= DefaultBufferSize;
	}
}

template<class T, GMemManagerFun MMFun>
void GDeque<T, MMFun>::assign(std::initializer_list<T> values)
{
	*this = values;
}

template<class T, GMemManagerFun MMFun>
void GDeque<T, MMFun>::assign(const GDeque& cv)
{
	*this = cv;
}

template<class T, GMemManagerFun MMFun>
void GDeque<T, MMFun>::swap(GDeque& deque)
{
	size_t temp_count = m_map_count;
	size_t temp_capcity = m_map_capcity;
	__deque_memory_buffer_block<T, MMFun>** temp_map = m_map;

	m_map = deque.m_map;
	m_map_count = deque.m_map_count;
	m_map_capcity = deque.m_map_capcity;

	deque.m_map = temp_map;
	m_map_count = temp_count;
	m_map_capcity = temp_capcity;
}

// 访问函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
T& GDeque<T, MMFun>::front()
{
	GASSERT(size() > 0);
	for (int index = 0; index < m_map_count; index++)
	{
		if (!m_map[index]->empty())
			return m_map[index]->m_data[0];
	}
}

template<class T, GMemManagerFun MMFun>
T& GDeque<T, MMFun>::back()
{
	GASSERT(size() > 0);
	for (int index = m_map_count-1; index >=0; index--)
	{
		if (!m_map[index]->empty())
			return m_map[index]->m_data[m_map[index]->size() - 1];
	}
}

//安插和移除
//*************************************************************************
template<class T, GMemManagerFun MMFun>
void GDeque<T, MMFun>::push_back(const T& cv)
{
	if (m_map[m_map_count - 1]->full())
		_create_new_buffer_block(m_map_count, DefaultBufferSize);
	m_map[m_map_count - 1]->push_back();
}



// 虚函数函数
//*************************************************************************

template<class T, GMemManagerFun MMFun>
bool GDeque<T, MMFun>::empty()
{
	if (m_map == nullptr)
		return true;
	bool is_empty = true;
	for (int index = 0; index < m_map_count; index++)
		is_empty = is_empty && m_map[index]->empty();
	return is_empty;
}

template<class T, GMemManagerFun MMFun>
size_t GDeque<T, MMFun>::size()
{
	if (m_map == nullptr)
		return 0;
	size_t num = 0;
	for (int index = 0; index < m_map_count; index++)
		num += m_map[index]->size();
	return num;
}

template<class T, GMemManagerFun MMFun>
void GDeque<T, MMFun>::clear()
{
	for (int index = 0; index < m_map_count; index++)
		m_map[index]->clear();
}



//迭代器函数
//*************************************************************************
template<class T>
_Deque_Iterator<T>& _Deque_Iterator<T>::operator++()
{
	_current++;
	if (_current == _last)
		jump_node(1);
	return *this;
}

template<class T>
_Deque_Iterator<T>& _Deque_Iterator<T>::operator--()
{
	if (_current == _first)
		jump_node(-1);
	_current--;
	return *this;
}

template<class T>
T& _Deque_Iterator<T>::operator*()
{
	return *_current;
}

template<class T>
T* _Deque_Iterator<T>::operator->()
{
	return &(operator*());
}

template<class T>
_Deque_Iterator<T> _Deque_Iterator<T>::operator++(int)
{
	_Deque_Iterator temp(_current, _first, _last, _node);
	--(*this);
	return temp;
}

template<class T>
_Deque_Iterator<T> _Deque_Iterator<T>::operator--(int)
{
	_Deque_Iterator temp(_current, _first, _last, _node);
	--(*this);
	return temp;
}

template<class T>
_Deque_Iterator<T> _Deque_Iterator<T>::operator+(distance idx)
{
	_Deque_Iterator temp(_current, _first, _last, _node);
	temp += idx;
	return temp;
}

template<class T>
_Deque_Iterator<T> _Deque_Iterator<T>::operator-(distance idx)
{
	_Deque_Iterator temp(_current, _first, _last, _node);
	temp -= idx;
	return temp;
}


template<class T>
_Deque_Iterator<T>& _Deque_Iterator<T>::operator+=(distance idx)
{
	_move_distance(idx);
	return *this;
}

template<class T>
_Deque_Iterator<T>& _Deque_Iterator<T>::operator-=(distance idx)
{
	_move_distance(-idx);
	return *this;
}

template<class T>
bool _Deque_Iterator<T>::operator==(const _Deque_Iterator& rhs)
{
	return _current == rhs._current &&
		   _first == rhs._first &&
		   _last == rhs._last &&
		   _node == rhs._node;
}

template<class T>
bool _Deque_Iterator<T>::operator!=(const _Deque_Iterator& rhs)
{
	return _current != rhs._current ||
		   _first != rhs._first ||
		   _last != rhs._last ||
		   _node != rhs._node;
}

template<class T>
ptrdiff_t _Deque_Iterator<T>::operator-(const _Deque_Iterator& rhs)
{
	size_t buffer_size = _node->m_capcity;
	distance node_dis = _node - rhs._node;
	if (node_dis == 0)
		return _current - rhs._current;
	else if(node_dis>0)
	{
		size_t node_delta = node_dis - 1;
		return node_delta * buffer_size + (_current - _first) + (rhs._last - rhs._current);
	}
	else
	{
		size_t node_delta = -node_dis - 1;
		return (node_delta * buffer_size + (_last - _current) + (rhs._current - rhs._first))*-1;
	}
}







