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
void __deque_memory_buffer_block<T, MMFun>::assign(size_t _capcity, size_t _count)
{
	for (int index = 0; index < _count && index < m_capcity; index++)
		_construct_no_cv(index);
}

template<class T, GMemManagerFun MMFun>
void __deque_memory_buffer_block<T, MMFun>::assign(size_t _capcity, size_t _count, const T& val)
{
	GASSERT(m_data != nullptr);
	for (int index = 0; index < _count && index < m_capcity; index++)
		_construct_idx(index, val);
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
_Deque_Iterator<T, MMFun> __deque_memory_buffer_block<T, MMFun>::insert(_iterator_type pos, const T& cv)
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

	for (int index = 0; index < m_map_count; index++)
	{
		_create_new_buffer_block(index);
		m_map[index] = cv.m_map[index];
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
			m_map[index]->assign(DefaultBufferSize, DefaultBufferSize);
		else
			m_map[index]->assign(DefaultBufferSize, _count);
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
			m_map[index]->assign(DefaultBufferSize, DefaultBufferSize, val);
		else
			m_map[index]->assign(DefaultBufferSize, _count, val);
		_count -= DefaultBufferSize;
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