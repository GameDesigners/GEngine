//构造函数 
//*************************************************************************

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector()
{
	m_data = this->New(DefaultCapcity);
	GASSERT(m_data != nullptr);
	m_count = 0;
	m_capcity = DefaultCapcity;
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(const GVector& cv)
{
	m_data = this->New(cv.m_capcity);
	GASSERT(m_data != nullptr);
	m_capcity = cv.m_capcity;
	m_count = cv.m_count;

	for (int index = 0; index < m_count; index++)
		*(m_data + index) = *(cv.m_data + index);
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(GVector&& rv)
{
	GASSERT(rv.m_data != nullptr);
	m_data = rv.m_data;
	m_count = rv.m_count;
	m_capcity = rv.m_capcity;
	rv.m_data = nullptr;
	rv.m_capcity = 0;
	rv.m_count = 0;
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(size_t _m_capcity)
{
	m_data = this->New(_m_capcity);
	GASSERT(m_data != nullptr);
	m_data = {};
	m_capcity = _m_capcity;
	m_count = 0;
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(size_t _m_count, const T& val)
{
	m_count = _m_count;
	m_capcity = DefaultCapcity;
	while (m_capcity < _m_count)
		m_capcity += IncreaseCapcityStep;

	m_data = this->New(m_capcity);
	GASSERT(m_data != nullptr);

	for (int index = 0; index < m_count; index++)
		*(m_data + index) = val;
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(iterator begin, iterator end)
{ 
	m_count = end - begin;
	m_capcity = DefaultCapcity;
	while (m_capcity < m_count)
		m_capcity += IncreaseCapcityStep;

	m_data = this->New(m_capcity);
	GASSERT(m_data != nullptr);
	for (int index = 0; index < m_count; index++)
		*(m_data + index) = *(begin + index);
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::GVector(std::initializer_list<T> values)
{
	m_count = values.size();
	m_capcity = DefaultCapcity;
	while (m_capcity < m_count)
		m_capcity += IncreaseCapcityStep;

	m_data = this->New(m_capcity);
	GASSERT(m_data != nullptr);

	int idx = 0;
	for (auto pval : values)
	{
		*(m_data + idx) = (T)(*pval);
		idx++;
	}
}

template<class T, GMemManagerFun MMFun>
GVector<T, MMFun>::~GVector()
{
	if (m_data != nullptr)
		this->Delete(m_data,m_count);
}


//赋值函数 
//*************************************************************************

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::operator=(const GVector& cv)
{
	size_t temp = m_capcity;
	while (temp <= cv.m_count)
		temp += IncreaseCapcityStep;

	if (temp != m_capcity)
	{
		T* new_memory = this->New(temp);
		GASSERT(new_memory != nullptr);
		m_capcity = temp;
		this->Delete(m_data, m_capcity);
		m_data = new_memory;
	}

	m_count = cv.m_count;
	for (int idx = 0; idx < m_count; idx++)
		*(m_data + idx) = *(cv.m_data + idx);
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::operator=(GVector&& rv)
{
	GASSERT(rv.m_data != nullptr);
	this->Delete(m_data, m_capcity);
	m_count = rv.m_count;
	m_capcity = rv.m_capcity;
	m_data = rv.m_data;

	rv.m_data = nullptr;
	rv.m_count = 0;
	rv.m_capcity = 0;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::operator=(std::initializer_list<T> values)
{
	size_t elem_num = values.size();
	size_t temp = m_capcity;
	while (temp < elem_num)
		temp += IncreaseCapcityStep;

	if (temp != m_capcity)
	{
		T* new_memory = this->New(temp);
		GASSERT(new_memory != nullptr);
		m_capcity = temp;
		this->Delete(m_data, m_capcity);
		m_data = new_memory;
	}
	m_count = elem_num;
	int idx = 0;
	for (auto pval : values)
	{
		*(m_data + idx) = (T)(*pval);
		idx++;
	}
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::assign(int _count, const T& val)
{
	size_t temp = m_capcity;
	while (temp < _count)
		temp += IncreaseCapcityStep;
	if (temp != m_capcity)
		reserve(temp);
	m_count = _count;
	m_capcity = temp;
	for (int index = 0; index < m_count; index++)
		*(m_data + index) = val;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::assign(iterator begin, iterator end)
{
	size_t _count = end - begin;
	size_t temp = m_capcity;
	while (temp < _count)
		temp += IncreaseCapcityStep;
	if (temp != m_capcity)
		reserve(temp);

	m_count = _count;
	m_capcity = temp;
	for (int index = 0; index < m_count; index++)
		*(m_data + index) = *(begin + index);
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::assign(std::initializer_list<T> values)
{
	size_t elem_num = values.size();
	size_t temp = m_capcity;
	while (temp < elem_num)
		temp += IncreaseCapcityStep;
	if (temp != m_capcity)
		reserve(temp);

	m_count = elem_num;
	m_capcity = temp;
	int idx = 0;
	for (auto pval : values)
	{
		*(m_data + idx) = (T)(*pval);
		idx++;
	}
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::swap(GVector& v)
{
	T* temp = m_data;
	size_t _count = m_count;
	size_t _capcity = m_capcity;

	m_data = v.m_data;
	m_count = v.m_count;
	m_capcity = v.m_capcity;

	v.m_data = temp;
	v.m_count = _count;
	v.m_capcity = _capcity;

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
		reserve(m_capcity + IncreaseCapcityStep);
	construct(m_data + m_count, cv);
	m_count++;
} 

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::push_back(T&& rv)
{
	if (m_count == m_capcity)
		reserve(m_capcity + IncreaseCapcityStep);
	m_data[m_count] = g_move(rv);
	m_count++;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::pop_back()
{
	if (m_count == 0)
		return;
	if (ValueBase<T>::NeedsDestructor)
		m_data[m_count - 1]->~T();
	m_count--;
}

template<class T, GMemManagerFun MMFun>
_Vector_Iterator<T>  GVector<T, MMFun>::insert(iterator_type pos, const T& val)
{
	if (m_count == m_capcity)
		reserve(m_capcity + IncreaseCapcityStep);

	iterator_type p = end();
	for (p; p != pos; p--)
		*p = *(p - 1);
	*p = val;
	m_count++;
	return p;
}

template<class T, GMemManagerFun MMFun>
_Vector_Iterator<T>  GVector<T, MMFun>::insert(iterator_type pos, size_t num, const T& val)
{
	if (num == 0)
		return pos;

	size_t temp = m_capcity;
	while (temp <= m_count + num)
		temp += IncreaseCapcityStep;
	if (temp != m_capcity)
		reserve(temp);

	iterator_type p = end();
	for (p; p != pos; p--)
		*(p + num - 1) = *(p - 1);

	for (int index = 0; index < num; index++)
	{
		*p = val;
		p--;
	}
	return p;
}

template<class T, GMemManagerFun MMFun>
_Vector_Iterator<T> GVector<T, MMFun>::insert(iterator_type pos, iterator_type _begin, iterator_type _end)
{
	size_t len = _end - _begin;
	if (len < 0)
		return pos;//迭代器开始和结束顺序不对

	size_t temp = m_capcity;
	while (temp <= m_count + len)
		temp += IncreaseCapcityStep;
	if (temp != m_capcity)
		reserve(temp);

	//向后挪动
	iterator_type p = end();
	for (p; p != pos; p--)
		*(p + len - 1) = *(p - 1);

	for (auto q = _begin; q != _end; q++,p--)
		*p = *q;
	return p;
}

template<class T, GMemManagerFun MMFun>
_Vector_Iterator<T> GVector<T, MMFun>::insert(iterator_type pos, std::initializer_list<T> values)
{
	size_t len = values.size();
	if (len < 0)
		return pos;//迭代器开始和结束顺序不对

	size_t temp = m_capcity;
	while (temp <= m_count + len)
		temp += IncreaseCapcityStep;
	if (temp != m_capcity)
		reserve(temp);

	//向后挪动
	iterator_type p = end();
	for (p; p != pos; p--)
		*(p + len - 1) = *(p - 1);

	for (auto q : values) 
	{
		*p = *q;
		p--;
	}
	return p;
}


template<class T, GMemManagerFun MMFun>
template<class ...Args>
_Vector_Iterator<T> GVector<T, MMFun>::emplace(iterator_type pos, Args&&... args)
{
	T temp(args...);
	return insert(pos, temp);
}

template<class T, GMemManagerFun MMFun>
template<class ...Args>
_Vector_Iterator<T> GVector<T, MMFun>::emplace_back(Args&&... args)
{
	T temp(args...);
	push_back(temp);
	return _Vector_Iterator<T>(m_data + m_count - 1);
}

template<class T, GMemManagerFun MMFun>
_Vector_Iterator<T> GVector<T, MMFun>::erase(iterator_type pos)
{
	if (ValueBase<T>::NeedsDestructor)
		pos->~T();

	for(auto p = pos; p + 1 != end(); p++)
		*p = *(p + 1);
	m_count--;		
}

template<class T, GMemManagerFun MMFun>
_Vector_Iterator<T> GVector<T, MMFun>::erase(iterator_type _begin, iterator_type _end)
{
	if (ValueBase<T>::NeedsDestructor)
		for (auto p = _begin; p != _end; p++)
			p->~T();

	for (auto p = _begin, q = _end; q != end(); p++, q++)
		*p = *q;
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

	size_t temp = m_capcity;
	while (temp <= num)
		temp += IncreaseCapcityStep;
	if (temp != m_capcity)
		reserve(temp);

	if (num > m_count)
		insert(end(), num - m_count, val);
	else
	{
		for (int index = 0; index < m_count - num; index++)
			pop_back();
	}
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
		for (int index = 0; index < m_count; index++)
			(m_data + index)->~T();
	m_count = 0;
}


//非更易型操作
//*************************************************************************

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::reserve(size_t _capcity)
{
	if (m_capcity >= _capcity)
		return;

	T* new_memory = this->New(_capcity);
	GASSERT(new_memory != nullptr);
	GMemoryCpy(new_memory, _capcity, m_data, m_count);
	this->Delete(m_data, m_capcity);
	m_data = new_memory;
	m_capcity = _capcity;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::shrink_to_fit()
{
	reserve(m_count);
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