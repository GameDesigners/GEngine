//构造函数 
//*************************************************************************

template<class T, size_t N>
GArray<T, N>::GArray() 
{

}


template<class T, size_t N>
GArray<T, N>::GArray(const GArray& cv)
{
	for (int index = 0; index < N; ++index)
		m_data[index] = cv.m_data[index];
}

template<class T, size_t N>
GArray<T, N>::GArray(GArray&& rv)
{
	for (int index = 0; index < N; ++index)
		m_data[index] = g_move(rv[index]);
}

template<class T, size_t N>
GArray<T, N>::GArray(iteractor_type _begin, iteractor_type _end)
{
	iteractor_type p = _begin;
	int idx = 0;
	for (p; p != _end; p++, idx++)
		m_data[idx] = *p;
}

template<class T, size_t N>
GArray<T, N>::GArray(std::initializer_list<T> values)
{
	T* p = (T*)values.begin();
	int idx = 0;
	for (p; p != values.end(); p++, idx++)
		*(m_data + idx) = *p;
}

template<class T, size_t N>
GArray<T, N>::~GArray() 
{
	if (ValueBase<T>::NeedsDestructor)
	{
		for (int index = 0; index < N; index++)
			m_data[index].~T();
	}
}


//赋值函数 
//*************************************************************************

template<class T, size_t N>
void GArray<T, N>::operator=(const GArray& cv)
{
	for (int index = 0; index < N; index++)
		m_data[index] = cv.m_data[index];
}

template<class T, size_t N>
void GArray<T, N>::operator=(GArray&& rv)
{
	for (int index = 0; index < N; index++)
		m_data[index] = g_move(rv[index]);
}
template<class T, size_t N>
void GArray<T, N>::operator=(std::initializer_list<T> values)
{
	T* p = (T*)values.begin();
	T* pm_data = &m_data[0];
	for (p; p != values.end(); p++, pm_data++)
		*pm_data = *p;
}

template<class T, size_t N>
void GArray<T, N>::fill(const T& val)
{
	for (int index = 0; index < N; ++index)
		m_data[index] = val;
}

template<class T, size_t N>
void GArray<T, N>::swap(GArray& v)
{
	for (int index = 0; index < N; ++index)
	{
		T tmp = m_data[index];
		m_data[index] = v[index];
		v[index] = tmp;
	}
}

//赋值函数 
//*************************************************************************

template<class T, size_t N>
T& GArray<T, N>::operator[](int idx)
{
	return m_data[idx];
}

template<class T, size_t N>
T& GArray<T, N>::at(int idx)
{
	GASSERT(idx < N);
	return m_data[idx];
}

template<class T, size_t N>
T& GArray<T, N>::front()
{
	return m_data[0];
}

template<class T, size_t N>
T& GArray<T, N>::back()
{
	return m_data[N - 1];
}


//虚函数重写 
//*************************************************************************

template<class T, size_t N>
bool GArray<T, N>::empty()
{
	return false;
}

template<class T, size_t N>
size_t GArray<T, N>::size()
{
	return N;
}

template<class T, size_t N>
size_t GArray<T, N>::capcity()
{
	return N;
}

template<class T, size_t N>
void GArray<T, N>::clear() {}


//运算符重载
//*************************************************************************

template<class T, size_t N>
bool GArray<T, N>::operator==(const GArray& rhs)
{
	for (int index = 0; index < N; ++index)
	{
		if (m_data[index] != rhs.m_data[index])
			return false;
	}
	return  true;
}

template<class T, size_t N>
bool GArray<T, N>::operator!=(const GArray& rhs)
{
	for (int index = 0; index < N; ++index)
	{
		if (m_data[index] != rhs.m_data[index])
			return true;
	}
	return false;
}

template<class T, size_t N>
bool GArray<T, N>::operator<(const GArray& rhs)
{
	for (int index = 0; index < N; ++index)
	{
		if (m_data[index] < rhs.m_data[index])
			return true;
		else if (m_data[index] > rhs.m_data[index])
			return false;
	}
	return false;
}

template<class T, size_t N>
bool GArray<T, N>::operator>(const GArray& rhs)
{
	for (int index = 0; index < N; ++index)
	{
		if (m_data[index] > rhs.m_data[index])
			return true;
		else if (m_data[index] < rhs.m_data[index])
			return false;
	}
	return false;
}

template<class T, size_t N>
bool GArray<T, N>::operator>=(const GArray& rhs)
{
	return *this > rhs || *this == rhs;
}

template<class T, size_t N>
bool GArray<T, N>::operator<=(const GArray& rhs)
{
	return *this < rhs || *this == rhs;
}


//迭代器
//*************************************************************************
template<class T, size_t N>
_Iterator<T> GArray<T, N>::begin()
{
	return _Iterator<T>(m_data);
}

template<class T, size_t N>
_Iterator<T> GArray<T, N>::end()
{
	return _Iterator<T>(m_data + N);
}

template<class T,size_t N>
_CIterator<T> GArray<T, N>::cbegin()
{
	return _CIterator<T>(m_data);
}

template<class T, size_t N>
_CIterator<T> GArray<T, N>::cend()
{
	return _CIterator<T>(m_data + N);
}

template<class T, size_t N>
_RIterator<T> GArray<T, N>::rbegin()
{
	return _RIterator<T>(m_data + N - 1);
}

template<class T, size_t N>
_RIterator<T> GArray<T, N>::rend()
{
	return _RIterator<T>(m_data - 1);
}

template<class T, size_t N>
_CRIterator<T> GArray<T, N>::crbegin()
{
	return _CRIterator<T>(m_data + N - 1);
}

template<class T, size_t N>
_CRIterator<T> GArray<T, N>::crend()
{
	return _CRIterator<T>(m_data - 1);
}
