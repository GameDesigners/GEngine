#include "GArray.h"
//构造函数 
//**********************************************************************************************************************************************

template<class T, size_t N>
GEngine::GStl::GArray<T, N>::GArray() {}


template<class T, size_t N>
GEngine::GStl::GArray<T, N>::GArray(const GArray& clone)
{
	for (int index = 0; index < N; ++index)
		m_data[index] = clone.m_data[index];
}

template<class T, size_t N>
GEngine::GStl::GArray<T, N>::GArray(GArray&& rv)
{
	for (int index = 0; index < N; ++index)
		m_data[index] = GMove(rv[index]);
}

template<class T, size_t N>
GEngine::GStl::GArray<T, N>::GArray(iterator_type begin_iterator, iterator_type end_iterator)
{
	iterator_type iterator = begin_iterator;
	int index = 0;
	for (iterator; iterator != end_iterator; iterator++, index++)
		m_data[index] = *iterator;
}

template<class T, size_t N>
GEngine::GStl::GArray<T, N>::GArray(std::initializer_list<T> values)
{
	T* intialize_iterator = (T*)values.begin();
	int index = 0;
	for (intialize_iterator; intialize_iterator != values.end(); intialize_iterator++, index++)
		m_data[index] = *intialize_iterator;
}

template<class T, size_t N>
GEngine::GStl::GArray<T, N>::~GArray() {}


//赋值函数 
//**********************************************************************************************************************************************

template<class T, size_t N>
void GEngine::GStl::GArray<T, N>::operator=(const GArray& clone)
{
	for (int index = 0; index < N; ++index)
		m_data[index] = clone.m_data[index];
}

template<class T, size_t N>
void GEngine::GStl::GArray<T, N>::operator=(GArray&& rv)
{
	for (int index = 0; index < N; ++index)
		m_data[index] = GMove(rv[index]);
}
template<class T, size_t N>
void GEngine::GStl::GArray<T, N>::operator=(std::initializer_list<T> values)
{
	T* p = (T*)values.begin();
	int index = 0;
	for (p; p != values.end(); p++, ++index)
		m_data[index] = *p;
}

template<class T, size_t N>
void GEngine::GStl::GArray<T, N>::fill(const T& value)
{
	for (int index = 0; index < N; ++index)
		m_data[index] = value;
}

template<class T, size_t N>
void GEngine::GStl::GArray<T, N>::swap(GArray& array)
{
	for (int index = 0; index < N; ++index)
	{
		T tmp = m_data[index];
		m_data[index] = array[index];
		array[index] = tmp;
	}
}

//赋值函数 
//**********************************************************************************************************************************************

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T,N>::reference GEngine::GStl::GArray<T, N>::operator[](size_type idx)
{
	return m_data[idx];
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::reference GEngine::GStl::GArray<T, N>::at(size_type idx)
{
	GASSERT(idx < N);
	return m_data[idx];
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::reference  GArray<T, N>::front()
{
	return m_data[0];
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::reference GArray<T, N>::back()
{
	return m_data[N - 1];
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::const_reference GEngine::GStl::GArray<T, N>::operator[](size_type idx) const
{
	return m_data[idx];
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::const_reference GEngine::GStl::GArray<T, N>::at(size_type idx) const
{
	GASSERT(idx < N);
	return m_data[idx];
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::const_reference  GArray<T, N>::front() const
{
	return m_data[0];
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::const_reference GArray<T, N>::back() const
{
	return m_data[N - 1];
}


template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::pointer GArray<T, N>::data() noexcept
{
	return m_data;
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::const_pointer GEngine::GStl::GArray<T, N>::data() const noexcept
{
	return m_data;
}


//虚函数重写 
//**********************************************************************************************************************************************

template<class T, size_t N>
constexpr bool GArray<T, N>::empty() const
{
	return N == 0;
}

template<class T, size_t N>
constexpr size_t GArray<T, N>::size() const
{
	return N;
}

template<class T, size_t N>
constexpr size_t GArray<T, N>::capcity() const
{
	return N;
}

template<class T, size_t N>
void GArray<T, N>::clear() {}


//运算符重载
//**********************************************************************************************************************************************

template<class T, size_t N>
bool GArray<T, N>::operator==(const GArray& rhs) const
{
	for (int index = 0; index < N; ++index)
	{
		if (m_data[index] != rhs.m_data[index])
			return false;
	}
	return  true;
}

template<class T, size_t N>
bool GArray<T, N>::operator!=(const GArray& rhs) const
{
	for (int index = 0; index < N; ++index)
	{
		if (m_data[index] != rhs.m_data[index])
			return true;
	}
	return false;
}

template<class T, size_t N>
bool GArray<T, N>::operator<(const GArray& rhs) const
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
bool GArray<T, N>::operator>(const GArray& rhs) const
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
bool GArray<T, N>::operator>=(const GArray& rhs) const
{
	return !(*this < rhs);
}

template<class T, size_t N>
bool GArray<T, N>::operator<=(const GArray& rhs) const
{
	return !(*this > rhs);
}


//迭代器
//**********************************************************************************************************************************************
template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::iterator_type GEngine::GStl::GArray<T, N>::begin()
{
	return iterator_type(m_data);
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::iterator_type GEngine::GStl::GArray<T, N>::end()
{
	return iterator_type(m_data + N);
}

template<class T,size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::c_iterator_type GEngine::GStl::GArray<T, N>::cbegin()
{
	return c_iterator_type(m_data);
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::c_iterator_type GEngine::GStl::GArray<T, N>::cend()
{
	return c_iterator_type(m_data + N);
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::r_iterator_type GEngine::GStl::GArray<T, N>::rbegin()
{
	return r_iterator_type(m_data + N - 1);
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::r_iterator_type GEngine::GStl::GArray<T, N>::rend()
{
	return r_iterator_type(m_data - 1);
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::cr_iterator_type GEngine::GStl::GArray<T, N>::crbegin()
{
	return cr_iterator_type(m_data + N - 1);
}

template<class T, size_t N>
constexpr typename GEngine::GStl::GArray<T, N>::cr_iterator_type GEngine::GStl::GArray<T, N>::crend()
{
	return cr_iterator_type(m_data - 1);
}
