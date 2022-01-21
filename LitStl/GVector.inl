#include "GVector.h"
//构造函数 
//**********************************************************************************************************************************************

template<class T, GMemManagerFun MMFun>
constexpr GEngine::GStl::GVector<T, MMFun>::GVector()
{
	m_data = this->New(DefaultCapcity);
	GASSERT(m_data != nullptr);
	m_count = 0;
	m_capcity = DefaultCapcity;
	m_constructed = 0;
}

template<class T, GMemManagerFun MMFun>
constexpr GEngine::GStl::GVector<T, MMFun>::GVector(const GVector& cv)
{
	m_data = this->New(cv.m_capcity);
	GASSERT(m_data != nullptr);
	m_count = cv.m_count;
	m_capcity = cv.m_capcity;

	for (size_type index = 0; index < m_count; ++index) 
		__construct_element_idx(index, *(cv.m_data + index));
}

template<class T, GMemManagerFun MMFun>
constexpr GEngine::GStl::GVector<T, MMFun>::GVector(GVector&& rv) noexcept
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
GEngine::GStl::GVector<T, MMFun>::GVector(size_type count)
{
	m_capcity = __caculate_increased_capcity(count);
	m_data = this->New(m_capcity);
	GASSERT(m_data != nullptr);
	m_count = count;
	for (int index = 0; index < m_count; ++index)
		__construct_elem_to_default_value(index);
}

template<class T, GMemManagerFun MMFun>
constexpr GEngine::GStl::GVector<T, MMFun>::GVector(size_type count, const_reference val)
{
	m_count = count;
	m_capcity = __caculate_increased_capcity(count);
	m_constructed = 0;

	m_data = this->New(m_capcity);
	GASSERT(m_data != nullptr);

	for (int index = 0; index < m_count; ++index) 
		__construct_element_idx(index, val);
}

template<class T, GMemManagerFun MMFun>
constexpr GEngine::GStl::GVector<T, MMFun>::GVector(iterator_type first, iterator_type last)
{ 
	m_count = last - first;
	GASSERT(m_count >= 0);  //迭代器异常断言
	m_capcity = __caculate_increased_capcity(m_count);
	m_constructed = 0;

	m_data = this->New(m_capcity);
	GASSERT(m_data != nullptr);

	for (int index = 0; index < m_count; ++index)
		__construct_element_idx(index, *(first + index));
}

template<class T, GMemManagerFun MMFun>
constexpr GEngine::GStl::GVector<T, MMFun>::GVector(std::initializer_list<T> values)
{
	m_count = values.size();
	m_capcity = __caculate_increased_capcity(m_count);
	m_constructed = 0;

	m_data = this->New(m_capcity);
	GASSERT(m_data != nullptr);

	int idx = 0;
	 for (T* p = (T*)values.begin(); p != values.end(); p++, idx++)
		 __construct_element_idx(idx, *p);
}

template<class T, GMemManagerFun MMFun>
GEngine::GStl::GVector<T, MMFun>::~GVector()
{
	if (m_data != nullptr)
		this->Delete(m_data, m_capcity, m_constructed);

	m_data = nullptr;
	m_count = 0;
	m_capcity = 0;
	m_constructed = 0;
}


//赋值函数 
//**********************************************************************************************************************************************

template<class T, GMemManagerFun MMFun>
constexpr GEngine::GStl::GVector<T,MMFun>& GEngine::GStl::GVector<T, MMFun>::operator=(const GVector& clone)
{
	size_t temp = __caculate_increased_capcity(clone.m_count, m_capcity);

	if (temp != m_capcity)
		__rellocate_memory_block(temp, false);

	m_count = clone.m_count;
	for (int index = 0; index < m_count; ++index)
		__construct_element_idx(index, *(clone.m_data + index));
	return *this;
}

template<class T, GMemManagerFun MMFun>
constexpr GEngine::GStl::GVector<T,MMFun>& GEngine::GStl::GVector<T, MMFun>::operator=(GVector&& rv)
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

	return *this;
}

template<class T, GMemManagerFun MMFun>
constexpr GEngine::GStl::GVector<T, MMFun>& GEngine::GStl::GVector<T, MMFun>::operator=(std::initializer_list<T> values)
{
	size_t elem_num = values.size();
	size_t temp = __caculate_increased_capcity(elem_num, m_capcity);
	if (temp != m_capcity)
		__rellocate_memory_block(temp, false);

	int idx = 0;
	for (T* p = (T*)values.begin(); p != values.end(); p++, idx++)
		__construct_element_idx(idx, *p);
	m_count = elem_num;

	return *this;
}

template<class T, GMemManagerFun MMFun>
constexpr void GEngine::GStl::GVector<T, MMFun>::assign(int count, const_reference value)
{
	size_t temp = __caculate_increased_capcity(count, m_capcity);
	if (temp != m_capcity)
		__rellocate_memory_block(temp, false);

	for (int index = 0; index < count; ++index)
		__construct_element_idx(index, value);
	m_count = count;
}

template<class T, GMemManagerFun MMFun>
constexpr void GEngine::GStl::GVector<T, MMFun>::assign(iterator_type first, iterator_type last)
{
	size_t count = last - first;
	GASSERT(count >= 0);  //迭代器异常断言
	size_t temp = __caculate_increased_capcity(count, m_capcity);
	
	if (temp != m_capcity)
		__rellocate_memory_block(temp, false);

	for (int index = 0; index < count; ++index)
		__construct_element_idx(index, *(first + index));
	m_count = count;
}

template<class T, GMemManagerFun MMFun>
constexpr void GEngine::GStl::GVector<T, MMFun>::assign(std::initializer_list<T> values)
{
	size_t elem_num = values.size();
	size_t temp = __caculate_increased_capcity(m_capcity);
	if (temp != m_capcity)
		__rellocate_memory_block(temp, false);

	int idx = 0;
	for (T* p = (T*)values.begin(); p != values.end(); p++, idx++)
		__construct_element_idx(idx, *p);
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
//**********************************************************************************************************************************************

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::reference GEngine::GStl::GVector<T, MMFun>::operator[](size_type idx)
{
	return m_data[idx];
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T,MMFun>::reference GEngine::GStl::GVector<T, MMFun>::at(size_type idx)
{
	GASSERT(idx < m_count);
	return m_data[idx];
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::reference GEngine::GStl::GVector<T, MMFun>::front()
{
	GASSERT(m_count != 0);
	return m_data[0];
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::reference GEngine::GStl::GVector<T, MMFun>::back()
{
	GASSERT(m_count != 0);
	return m_data[m_count - 1];
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::pointer GEngine::GStl::GVector<T, MMFun>::data() noexcept
{
	return m_data;
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::const_reference GEngine::GStl::GVector<T, MMFun>::operator[](size_type idx) const
{
	return m_data[idx];
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::const_reference GEngine::GStl::GVector<T, MMFun>::at(size_type idx) const
{
	GASSERT(idx < m_count);
	return m_data[idx];
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::const_reference GEngine::GStl::GVector<T, MMFun>::front() const
{
	GASSERT(m_count != 0);
	return m_data[0];
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::const_reference GEngine::GStl::GVector<T, MMFun>::back() const
{
	GASSERT(m_count != 0);
	return m_data[m_count - 1];
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::const_pointer GEngine::GStl::GVector<T, MMFun>::data() const
{
	return m_data;
}

//安插和移除
//**********************************************************************************************************************************************

template<class T, GMemManagerFun MMFun>
constexpr void GEngine::GStl::GVector<T, MMFun>::push_back(const_reference cr)
{
	if (m_count == m_capcity)
		__rellocate_memory_block(m_capcity + IncreaseCapcityStep, true);

	__construct_element_addr(m_data + m_count, cr);
	m_count++;
} 

template<class T, GMemManagerFun MMFun>
constexpr void GEngine::GStl::GVector<T, MMFun>::push_back(T&& rv)
{
	if (m_count == m_capcity)
		__rellocate_memory_block(m_capcity + IncreaseCapcityStep, true);
	__construct_elem_to_default_value(m_count);
	m_data[m_count] = GMove(rv);
	m_count++;
}

template<class T, GMemManagerFun MMFun>
constexpr void GEngine::GStl::GVector<T, MMFun>::pop_back()
{
	if (m_count == 0)
		return;

	__destruct_elem_idx(m_count - 1);
	m_count--;
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::iterator_type  GEngine::GStl::GVector<T, MMFun>::insert(iterator_type pos, const_reference value)
{
	iterator_type iterator = end();
	if (iterator - pos < 0)
		return pos;

	if (m_count == m_capcity)
		__rellocate_memory_block(m_capcity + IncreaseCapcityStep, true);

	for (iterator; iterator != pos; iterator--)
		__construct_element_iterator(iterator, *(iterator - 1));
	__construct_element_iterator(iterator, value);
	m_count++;
	return iterator;
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::iterator_type GEngine::GStl::GVector<T, MMFun>::insert(iterator_type pos, T&& rv)
{
	iterator_type iterator = end();
	if (iterator - pos < 0)
		return pos;

	if (m_count == m_capcity)
		__rellocate_memory_block(m_capcity + IncreaseCapcityStep, true);

	for (iterator; iterator != pos; iterator--)
		__construct_element_iterator(iterator, *(iterator - 1));
	
	*iterator = GMove(rv);

	m_count++;
	return iterator;
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::iterator_type GEngine::GStl::GVector<T, MMFun>::insert(iterator_type pos, size_type count, const_reference value)
{
	if (count == 0)
		return pos;

	iterator_type iterator = end();
	GASSERT(iterator - pos >= 0);  //传入迭代器是否合法断言

	size_t temp = __caculate_increased_capcity(count + m_count, m_capcity);
	if (temp != m_capcity)
		__rellocate_memory_block(temp, true);
	for (int index = 0; index < count; ++index)
		__construct_elem_to_default_value(m_count + index);

	//元素挪动
	for (iterator; iterator != pos; iterator--)
		__construct_element_iterator(iterator + count - 1, *(iterator - 1));

	//插入新值
	for (int index = 0; index < count; ++index, pos++)
		__construct_element_iterator(pos, value);
	m_count += count;
	return iterator;
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::iterator_type GEngine::GStl::GVector<T, MMFun>::insert(iterator_type pos, iterator_type first, iterator_type last)
{
	size_t count = last - first;
	iterator_type iterator = end();

	if (count < 0 || iterator - pos <= 0)
		return pos;//迭代器开始和结束顺序不对

	size_t temp = __caculate_increased_capcity(count, m_capcity);
	if (temp != m_capcity)
		__rellocate_memory_block(temp, true);
	for (int index = 0; index < count; ++index)
		__construct_elem_to_default_value(m_count + index);

	//向后挪动
	for (iterator; iterator != pos; iterator--)
		__construct_element_iterator(iterator + count - 1, *(iterator - 1));

	for (auto q = first; q != last; q++, pos++)
		__construct_element_iterator(pos, *q);
	m_count += count;
	return iterator;
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::iterator_type GEngine::GStl::GVector<T, MMFun>::insert(iterator_type pos, std::initializer_list<T> values)
{
	size_t count = values.size();
	iterator_type iterator = end();
	if (count < 0 || iterator - pos < 0)
		return pos;//迭代器开始和结束顺序不对

	size_t temp = __caculate_increased_capcity(m_count + count, m_capcity);
	if (temp != m_capcity)
		__rellocate_memory_block(temp, true);

	for (int index = 0; index < count; index++)
		__construct_elem_to_default_value(m_count + index);

	//向后挪动
	for (iterator; iterator != pos; iterator--)
		__construct_element_iterator(iterator + count - 1, *(iterator - 1));


	for (T* q = (T*)values.begin(); q != values.end(); q++, pos++)
		__construct_element_iterator(pos, *q);
	m_count += count;
	return iterator;
}


template<class T, GMemManagerFun MMFun>
template<class ...Args>
typename GEngine::GStl::GVector<T, MMFun>::iterator_type GEngine::GStl::GVector<T, MMFun>::emplace(iterator_type pos, Args&&... args)
{
	T temp(args...);
	return insert(pos, temp);
}

template<class T, GMemManagerFun MMFun>
template<class ...Args>
typename GEngine::GStl::GVector<T, MMFun>::iterator_type GEngine::GStl::GVector<T, MMFun>::emplace_back(Args&&... args)
{
	T temp(args...);
	push_back(temp);
	return iterator_type(m_data + m_count - 1);
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::iterator_type GEngine::GStl::GVector<T, MMFun>::erase(iterator_type pos)
{
	int idx = pos - begin();
	for (auto p = pos; p + 1 != end(); p++)
		__construct_element_iterator(p, *(p + 1));
	__destruct_elem_idx(m_count-1);
	m_count--;		
	return iterator_type(m_data + idx);
}

template<class T, GMemManagerFun MMFun>
constexpr typename GEngine::GStl::GVector<T, MMFun>::iterator_type GEngine::GStl::GVector<T, MMFun>::erase(iterator_type first, iterator_type last)
{
	int delete_count = last - first;
	if (delete_count <= 0)
		return first;

	int next_idx = end() - last;
	for (auto p = first, q = last; q != end(); p++, q++)
		__construct_element_iterator(p, *q);

	for (int index = 0; index < delete_count; ++index)
		__destruct_elem_idx(m_count - index - 1);
	m_count -= delete_count;
	return iterator_type(m_data + m_count - next_idx);
}

template<class T, GMemManagerFun MMFun>
constexpr void GEngine::GStl::GVector<T, MMFun>::resize(size_type count)
{
	resize(count, T());
}

template<class T, GMemManagerFun MMFun>
constexpr void GEngine::GStl::GVector<T, MMFun>::resize(size_type count, const_reference value)
{
	if (m_count == count)
		return;

	size_t temp = __caculate_increased_capcity(count, m_capcity);
	if (temp != m_capcity)
		__rellocate_memory_block(temp, true);

	int delta = count - m_count;
	if (delta > 0)
		insert(end(), delta, value);
	else
		erase(end() + delta, end());
}


//虚函数重写 
//**********************************************************************************************************************************************

template<class T, GMemManagerFun MMFun>
constexpr bool GEngine::GStl::GVector<T, MMFun>::empty() const
{
	return m_count == 0;
}

template<class T, GMemManagerFun MMFun>
constexpr size_t GEngine::GStl::GVector<T, MMFun>::size() const
{
	return m_count;
}

template<class T, GMemManagerFun MMFun>
constexpr size_t GEngine::GStl::GVector<T, MMFun>::capcity() const
{
	return m_capcity;
}

template<class T, GMemManagerFun MMFun>
void GVector<T, MMFun>::clear()
{
	if (ValueBase<T>::NeedsDestructor)
		while (m_constructed > 0)
			__destruct_elem_idx(m_constructed - 1);

	m_count = 0;
}


//非更易型操作
//**********************************************************************************************************************************************

template<class T, GMemManagerFun MMFun>
constexpr void GEngine::GStl::GVector<T, MMFun>::reserve(size_type new_cap)
{
	if (m_capcity >= new_cap)
		return;

	__rellocate_memory_block(new_cap, true);
}

template<class T, GMemManagerFun MMFun>
constexpr void GEngine::GStl::GVector<T, MMFun>::shrink_to_fit()
{
	if (m_capcity == m_count)
		return;
	__rellocate_memory_block(m_count, true);
}


//运算符重载
//**********************************************************************************************************************************************

template<class T, GMemManagerFun MMFun>
bool GEngine::GStl::GVector<T, MMFun>::operator==(const GVector& rhs) const
{
	if (m_count != rhs.m_count)
		return false;

	for (int index = 0; index < m_count; ++index)
	{
		if (*(m_data + index) != *(rhs.m_data + index))
			return false;
	}
	return true;
}

template<class T, GMemManagerFun MMFun>
bool GEngine::GStl::GVector<T, MMFun>::operator!=(const GVector& rhs) const
{
	if (m_count != rhs.m_count)
		return true;

	for (int index = 0; index < m_count; ++index)
	{
		if (*(m_data + index) != *(rhs.m_data + index))
			return true;
	}
	return false;
}

template<class T, GMemManagerFun MMFun>
bool GEngine::GStl::GVector<T, MMFun>::operator<(const GVector& rhs) const
{
	size_t min_count = m_count < rhs.m_count ? m_count : rhs.m_count;
	for (int index = 0; index < min_count; ++index)
	{
		if (*(m_data + index) < *(rhs.m_data + index))
			return true;
	}
	return m_count < rhs.m_count;
}

template<class T, GMemManagerFun MMFun>
bool GEngine::GStl::GVector<T, MMFun>::operator>(const GVector& rhs) const
{
	size_t min_count = m_count < rhs.m_count ? m_count : rhs.m_count;
	for (int index = 0; index < min_count; ++index)
	{
		if (*(m_data + index) > *(rhs.m_data + index))
			return true;
	}
	return m_count > rhs.m_count;
}

template<class T, GMemManagerFun MMFun>
bool GEngine::GStl::GVector<T, MMFun>::operator>=(const GVector& rhs) const
{
	return !(*this < rhs);
}

template<class T, GMemManagerFun MMFun>
bool GEngine::GStl::GVector<T, MMFun>::operator<=(const GVector& rhs) const
{
	return !(*this > rhs);
}

//迭代器
//**********************************************************************************************************************************************

template<class T, GMemManagerFun MMFun>
typename GEngine::GStl::GVector<T, MMFun>::iterator_type GEngine::GStl::GVector<T, MMFun>::begin()
{
	typedef GVector<T, MMFun>::iterator_type category;
	return iterator_type(m_data);
}

template<class T, GMemManagerFun MMFun>
typename GVector<T, MMFun>::iterator_type GVector<T, MMFun>::end()
{
	typedef GVector<T, MMFun>::iterator_type category;
	return iterator_type(m_data + m_count);
}

template<class T, GMemManagerFun MMFun>
typename GVector<T, MMFun>::c_iterator_type GVector<T, MMFun>::cbegin()
{
	typedef GVector<T, MMFun>::c_iterator_type category;
	return c_iterator_type(m_data);
}

template<class T, GMemManagerFun MMFun>
typename GVector<T, MMFun>::c_iterator_type GVector<T, MMFun>::cend()
{
	typedef GVector<T, MMFun>::c_iterator_type category;
	return c_iterator_type(m_data + m_count);
}

template<class T, GMemManagerFun MMFun>
typename GVector<T, MMFun>::r_iterator_type GVector<T, MMFun>::rbegin()
{
	typedef GVector<T, MMFun>::r_iterator_type category;
	return r_iterator_type(m_data + m_count - 1);
}

template<class T, GMemManagerFun MMFun>
typename GVector<T, MMFun>::r_iterator_type GVector<T, MMFun>::rend()
{
	typedef GVector<T, MMFun>::r_iterator_type category;
	return r_iterator_type(m_data - 1);
}

template<class T, GMemManagerFun MMFun>
typename GVector<T, MMFun>::cr_iterator_type GVector<T, MMFun>::crbegin()
{
	typedef GVector<T, MMFun>::cr_iterator_type category;
	return cr_iterator_type(m_data + m_count - 1);
}

template<class T, GMemManagerFun MMFun>
typename GVector<T, MMFun>::cr_iterator_type GVector<T, MMFun>::crend()
{
	typedef GVector<T, MMFun>::cr_iterator_type category;
	return cr_iterator_type(m_data - 1);
}