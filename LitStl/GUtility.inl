//构造函数 
//*************************************************************************

template<typename T1, typename T2>
GPair<T1, T2>::GPair() {}

template<typename T1, typename T2>
GPair<T1, T2>::GPair(const T1& _first, const T2& _second)
{
	first = _first;
	second = _second;
}

template<typename T1, typename T2>
GPair<T1, T2>::GPair(T1&& _first, T2&& _second) noexcept
{
	first = _first;
	second = _second;
}

template<typename T1,typename T2>
GPair<T1, T2>::GPair(const GPair& rhs)
{
	first = rhs.first;
	second = rhs.second;
}

template<typename T1,typename T2>
GPair<T1, T2>::GPair(GPair&& rv) noexcept
{
	*this = static_cast<GPair&&>(rv);
}



//析构函数
//*************************************************************************

template<typename T1, typename T2>
GPair<T1, T2>::~GPair() {}


//成员函数
//*************************************************************************

template<typename T1, typename T2>
void GPair<T1, T2>::swap(GPair<T1, T2>& value)
{
	GPair<T1, T2> temp(value);
	value = g_move(*this);
	*this = g_move(temp);
}

//符号重载函数
//*************************************************************************

template<typename T1, typename T2>
GPair<T1, T2>& GPair<T1, T2>::operator=(const GPair<T1,T2>& rhs)
{
	first = rhs.first;
	second = rhs.second;
	return *this;
}

template<typename T1, typename T2>
GPair<T1, T2>& GPair<T1, T2>::operator=(GPair<T1, T2>&& rv) noexcept
{
	first = static_cast<T1&&>(rv.first);
	second = static_cast<T2&&>(rv.second);
	return *this;
}

template<typename T1, typename T2>
bool GPair<T1, T2>::operator==(const GPair& rhs)
{
	return first == rhs.first && second == rhs.second;
}

template<typename T1, typename T2>
bool GPair<T1, T2>::operator!=(const GPair& rhs)
{
	return first != rhs.first || second != rhs.second;
}

template<typename T1, typename T2>
bool GPair<T1, T2>::operator<(const GPair& rhs)
{
	if (first != rhs.first)
		return first < rhs.first;
	else
		return second < rhs.second;
}

template<typename T1, typename T2>
bool GPair<T1, T2>::operator>(const GPair& rhs)
{
	if (first != rhs.first)
		return first > rhs.first;
	else
		return second > rhs.second;
}

template<typename T1, typename T2>
bool GPair<T1, T2>::operator<=(const GPair& rhs)
{
	return *this < rhs || *this == rhs;
}

template<typename T1, typename T2>
bool GPair<T1, T2>::operator>=(const GPair& rhs)
{
	return *this > rhs || *this == rhs;
}







