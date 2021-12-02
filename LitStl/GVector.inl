//构造函数 
//*************************************************************************

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector()
{
	m_data = this->New(DefaultCapcity);
	GASSERT(m_data != nullptr);
	m_count = 0;
	m_capcity = DefaultCapcity;
	m_constructed = 0;
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(const GVector& cv)
{
	m_data = this->New(cv.m_capcity);
	GASSERT(m_data != nullptr);
	m_count = cv.m_count;
	m_capcity = cv.m_capcity;

	for (int index = 0; index < m_count; index++) 
		_construct_elem(index, *(cv.m_data + index));
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(GVector&& rv)
{
	GASSERT(rv.m_data != nullptr);
	m_data = rv.m_data;
	m_count = rv.m_count;
	m_capcity = rv.m_capcity;
	m_constructed = rv.m_constructed;

	//将传入的右值数值重置(因为数据已经被移动)
	rv.m_data = nullptr;
	rv.m_capcity = 0;
	rv.m_count = 0;
	rv.m_constructed = 0;
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(size_t _count)
{
	m_capcity = _caculate_increased_capcity(_count);
	m_data = this->New(m_capcity);
	GASSERT(m_data != nullptr);
	m_count = _count;
	for (int index = 0; index < m_count; index++)
		_construct_elem_no_cv(index);
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(size_t _count, const T& val)
{
	m_count = _count;
	m_capcity = _caculate_increased_capcity(_count);
	m_constructed = 0;

	m_data = this->New(m_capcity);
	GASSERT(m_data != nullptr);

	for (int index = 0; index < m_count; index++) 
		_construct_elem(index, val);
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(_base_iterator _begin, _base_iterator _end)
{ 
	m_count = _end - _begin;
	GASSERT(m_count >= 0);  //迭代器异常断言
	m_capcity = _caculate_increased_capcity(m_count);
	m_constructed = 0;

	m_data = this->New(m_capcity);
	GASSERT(m_data != nullptr);

	for (int index = 0; index < m_count; index++)
		_construct_elem(index, *(_begin + index));
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(std::initializer_list<T> values)
{
	m_count = values.size();
	m_capcity = _caculate_increased_capcity(m_count);
	m_constructed = 0;

	m_data = this->New(m_capcity);
	GASSERT(m_data != nullptr);

	int idx = 0;
	 for (T* p = (T*)values.begin(); p != values.end(); p++, idx++)
		 _construct_elem(idx, *p);
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::~GVector()
{
	if (m_data != nullptr)
		this->Delete(m_data, m_capcity, m_constructed);

	m_data = nullptr;
	m_count = 0;
	m_capcity = 0;
	m_constructed = 0;
}


//赋值函数 
//*************************************************************************

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::operator=(const GVector& cv)
{
	size_t temp = _caculate_increased_capcity(cv.m_count, m_capcity);

	if (temp != m_capcity)
		_new_data_memory_addr(temp, false);
	m_count = cv.m_count;
	for (int idx = 0; idx < m_count; idx++)
		_construct_elem(idx, *(cv.m_data + idx));
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::operator=(GVector&& rv)
{
	GASSERT(rv.m_data != nullptr);
	this->Delete(m_data, m_capcity, m_constructed);  //删除本容器的数据

	m_data = rv.m_data;
	m_count = rv.m_count;
	m_capcity = rv.m_capcity;
	m_constructed = rv.m_constructed;

	rv.m_data = nullptr;
	rv.m_count = 0;
	rv.m_capcity = 0;
	m_constructed = 0;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::operator=(std::initializer_list<T> values)
{
	size_t elem_num = values.size();
	size_t temp = _caculate_increased_capcity(elem_num, m_capcity);
	if (temp != m_capcity)
		_new_data_memory_addr(temp, false);

	int idx = 0;
	for (T* p = (T*)values.begin(); p != values.end(); p++, idx++)
		_construct_elem(idx, *p);
	m_count = elem_num;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::assign(int _count, const T& val)
{
	size_t temp = _caculate_increased_capcity(_count, m_capcity);
	if (temp != m_capcity)
		_new_data_memory_addr(temp, false);

	for (int index = 0; index < _count; index++)
		_construct_elem(index, val);
	m_count = _count;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::assign(_base_iterator begin, _base_iterator end)
{
	size_t _count = end - begin;
	GASSERT(_count >= 0);  //迭代器异常断言
	size_t temp = _caculate_increased_capcity(_count,m_capcity);
	
	if (temp != m_capcity)
		_new_data_memory_addr(temp, false);

	for (int index = 0; index < _count; index++)
		_construct_elem(index, *(begin + index));
	m_count = _count;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::assign(std::initializer_list<T> values)
{
	size_t elem_num = values.size();
	size_t temp = _caculate_increased_capcity(m_capcity);
	if (temp != m_capcity)
		_new_data_memory_addr(temp, false);

	int idx = 0;
	for (T* p = (T*)values.begin(); p != values.end(); p++, idx++)
		_construct_elem(idx, *p);
	m_count = elem_num;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::swap(GVector& v)
{
	T* temp = m_data;
	size_t _count = m_count;
	size_t _capcity = m_capcity;
	size_t _constructed = m_constructed;

	m_data = v.m_data;
	m_count = v.m_count;
	m_capcity = v.m_capcity;
	m_constructed = v.m_constructed;

	v.m_data = temp;
	v.m_count = _count;
	v.m_capcity = _capcity;
	v.m_constructed = _constructed;

}


//赋值函数 
//*************************************************************************

template<class T, GMemManagerFun MMFun>
T& GVector<T, MMFun>::operator[](size_t idx)
{
	return m_data[idx];
}

template<class T, GMemManagerFun MMFun>
T& GVector<T, MMFun>::at(size_t idx)
{
	GASSERT(idx < m_count);
	return m_data[idx];
}

template<class T, GMemManagerFun MMFun>
T& GVector<T, MMFun>::front()
{
	GASSERT(m_count != 0);
	return m_data[0];
}

template<class T, GMemManagerFun MMFun>
T& GVector<T, MMFun>::back()
{
	GASSERT(m_count != 0);
	return m_data[m_count - 1];
}

//安插和移除
//*************************************************************************

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::push_back(const T& cv)
{
	if (m_count == m_capcity)
		_new_data_memory_addr(m_capcity + IncreaseCapcityStep, true);

	_construct_addr(m_data + m_count, cv);
	m_count++;
} 

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::push_back(T&& rv)
{
	if (m_count == m_capcity)
		_new_data_memory_addr(m_capcity + IncreaseCapcityStep, true);
	_construct_elem_no_cv(m_count);
	m_data[m_count] = g_move(rv);
	m_count++;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::pop_back()
{
	if (m_count == 0)
		return;

	_destruct_elem(m_count - 1);
	m_count--;
}

template<class T, GMemManagerFun MMFun>
_Base_Iterator<T>  GVector<T, MMFun>::insert(_base_iterator pos, const T& val)
{
	iterator_type p = end();
	if (p - pos < 0)
		return pos;

	if (m_count == m_capcity)
		_new_data_memory_addr(m_capcity + IncreaseCapcityStep, true);

	for (p; p != pos; p--)
		_construct_iterator(p, *(p - 1));
	_construct_iterator(p, val);
	m_count++;
	return p;
}

template<class T, GMemManagerFun MMFun>
_Base_Iterator<T>  GVector<T, MMFun>::insert(_base_iterator pos, size_t num, const T& val)
{
	if (num == 0)
		return pos;

	iterator_type p = end();
	GASSERT(p - pos >= 0);  //传入迭代器是否合法断言

	size_t temp = _caculate_increased_capcity(num + m_count, m_capcity);
	if (temp != m_capcity)
		_new_data_memory_addr(temp, true);
	for (int index = 0; index < num; index++)
		_construct_elem_no_cv(m_count + index);

	//元素挪动
	for (p; p != pos; p--)
		_construct_iterator(p + num - 1, *(p - 1));

	//插入新值
	for (int index = 0; index < num; index++, pos++)
		_construct_iterator(pos, val);
	m_count += num;
	return p;
}

template<class T, GMemManagerFun MMFun>
_Base_Iterator<T> GVector<T, MMFun>::insert(_base_iterator pos, _base_iterator _begin, _base_iterator _end)
{
	size_t _count = _end - _begin;
	iterator_type p = end();
	if (_count < 0 || p - pos <= 0)
		return pos;//迭代器开始和结束顺序不对

	size_t temp = _caculate_increased_capcity(_count, m_capcity);
	if (temp != m_capcity)
		_new_data_memory_addr(temp, true);
	for (int index = 0; index < _count; index++)
		_construct_elem_no_cv(m_count + index);

	//向后挪动
	for (p; p != pos; p--)
		_construct_iterator(p + _count - 1, *(p - 1));

	for (auto q = _begin; q != _end; q++, pos++)
		_construct_iterator(pos, *q);
	m_count += _count;
	return p;
}

template<class T, GMemManagerFun MMFun>
_Base_Iterator<T> GVector<T, MMFun>::insert(_base_iterator pos, std::initializer_list<T> values)
{
	size_t _count = values.size();
	iterator_type p = end();
	if (_count < 0 || p - pos < 0)
		return pos;//迭代器开始和结束顺序不对

	size_t temp = _caculate_increased_capcity(m_count + _count, m_capcity);
	if (temp != m_capcity)
		_new_data_memory_addr(temp, true);
	for (int index = 0; index < _count; index++)
		_construct_elem_no_cv(m_count + index);

	//向后挪动
	for (p; p != pos; p--)
		_construct_iterator(p + _count - 1, *(p - 1));


	for (T* q = (T*)values.begin(); q != values.end(); q++, pos++)
		_construct_iterator(pos, *q);
	m_count += _count;
	return p;
}


template<class T, GMemManagerFun MMFun>
template<class ...Args>
_Base_Iterator<T> GVector<T, MMFun>::emplace(_base_iterator pos, Args&&... args)
{
	T temp(args...);
	return insert(pos, temp);
}

template<class T, GMemManagerFun MMFun>
template<class ...Args>
_Base_Iterator<T> GVector<T, MMFun>::emplace_back(Args&&... args)
{
	T temp(args...);
	push_back(temp);
	return _Vector_Iterator<T>(m_data + m_count - 1);
}

template<class T, GMemManagerFun MMFun>
_Base_Iterator<T> GVector<T, MMFun>::erase(_base_iterator pos)
{
	int idx = pos - begin();
	for (auto p = pos; p + 1 != end(); p++)
		_construct_iterator(p, *(p + 1));
	_destruct_elem(m_count-1);
	m_count--;		
	return _Vector_Iterator<T>(m_data + idx);
}

template<class T, GMemManagerFun MMFun>
_Base_Iterator<T> GVector<T, MMFun>::erase(_base_iterator _begin, _base_iterator _end)
{
	int _delete_count = _end - _begin;
	if (_delete_count <= 0)
		return _begin;

	int next_idx = end() - _end;
	for (auto p = _begin, q = _end; q != end(); p++, q++)
		_construct_iterator(p, *q);

	for (int i = 0; i < _delete_count; i++)
		_destruct_elem(m_count - i-1);
	m_count -= _delete_count;
	return _Base_Iterator<T>(m_data + m_count - next_idx);
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::resize(size_t num)
{
	T val;
	resize(num, val);
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::resize(size_t num, const T& val)
{
	if (m_count == num)
		return;

	size_t temp = _caculate_increased_capcity(num, m_capcity);
	if (temp != m_capcity)
		_new_data_memory_addr(temp, true);

	int delta = num - m_count;
	if (delta > 0)
		insert(end(), delta, val);
	else
		erase(end() + delta, end());
}


//虚函数重写 
//*************************************************************************

template<class T, GMemManagerFun MMFun>
bool GVector<T, MMFun>::empty()
{
	return m_count == 0;
}

template<class T, GMemManagerFun MMFun>
size_t GVector<T, MMFun>::size()
{
	return m_count;
}

template<class T, GMemManagerFun MMFun>
size_t GVector<T, MMFun>::capcity()
{
	return m_capcity;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::clear()
{
	if (ValueBase<T>::NeedsDestructor)
		while (m_constructed > 0)
			_destruct_elem(m_constructed - 1);

	m_count = 0;
}


//非更易型操作
//*************************************************************************

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::reserve(size_t _capcity)
{
	if (m_capcity >= _capcity)
		return;

	_new_data_memory_addr(_capcity, true);
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::shrink_to_fit()
{
	if (m_capcity == m_count)
		return;
	_new_data_memory_addr(m_count, true);
}


//运算符重载
//*************************************************************************

template<class T, GMemManagerFun MMFun>
bool GVector<T, MMFun>::operator==(const GVector& rhs)
{
	if (m_count != rhs.m_count)
		return false;

	for (int index = 0; index < m_count; index++)
	{
		if (*(m_data + index) != *(rhs.m_data + index))
			return false;
	}
	return true;
}

template<class T, GMemManagerFun MMFun>
bool GVector<T, MMFun>::operator!=(const GVector& rhs)
{
	if (m_count != rhs.m_count)
		return true;

	for (int index = 0; index < m_count; index++)
	{
		if (*(m_data + index) != *(rhs.m_data + index))
			return true;
	}
	return false;
}

template<class T, GMemManagerFun MMFun>
bool GVector<T, MMFun>::operator<(const GVector& rhs)
{
	size_t min_count = m_count < rhs.m_count ? m_count : rhs.m_count;
	for (int index = 0; index < min_count; index++)
	{
		if (*(m_data + index) < *(rhs.m_data + index))
			return true;
	}
	return m_count < rhs.m_count;
}

template<class T, GMemManagerFun MMFun>
bool GVector<T, MMFun>::operator>(const GVector& rhs)
{
	size_t min_count = m_count < rhs.m_count ? m_count : rhs.m_count;
	for (int index = 0; index < min_count; index++)
	{
		if (*(m_data + index) > *(rhs.m_data + index))
			return true;
	}
	return m_count > rhs.m_count;
}

template<class T, GMemManagerFun MMFun>
bool GVector<T, MMFun>::operator>=(const GVector& rhs)
{
	return *this == rhs || *this > rhs;
}

template<class T, GMemManagerFun MMFun>
bool GVector<T, MMFun>::operator<=(const GVector& rhs)
{
	return *this == rhs || *this < rhs;
}

//迭代器
//*************************************************************************

template<class T, GMemManagerFun MMFun>
_Vector_Iterator<T> GVector<T, MMFun>::begin()
{
	return _Vector_Iterator<T>(m_data);
}

template<class T, GMemManagerFun MMFun>
_Vector_Iterator<T> GVector<T, MMFun>::end()
{
	return _Vector_Iterator<T>(m_data + m_count);
}

template<class T, GMemManagerFun MMFun>
_Vector_CIterator<T> GVector<T, MMFun>::cbegin()
{
	return _Vector_CIterator<T>(m_data);
}

template<class T, GMemManagerFun MMFun>
_Vector_CIterator<T> GVector<T, MMFun>::cend()
{
	return _Vector_CIterator<T>(m_data + m_count);
}

template<class T, GMemManagerFun MMFun>
_Vector_RIterator<T> GVector<T, MMFun>::rbegin()
{
	return _Vector_RIterator<T>(m_data + m_count - 1);
}

template<class T, GMemManagerFun MMFun>
_Vector_RIterator<T> GVector<T, MMFun>::rend()
{
	return _Vector_RIterator<T>(m_data - 1);
}

template<class T, GMemManagerFun MMFun>
_Vector_CRIterator<T> GVector<T, MMFun>::crbegin()
{
	return _Vector_CRIterator<T>(m_data + m_count - 1);
}

template<class T, GMemManagerFun MMFun>
_Vector_CRIterator<T> GVector<T, MMFun>::crend()
{
	return _Vector_CRIterator<T>(m_data - 1);
}