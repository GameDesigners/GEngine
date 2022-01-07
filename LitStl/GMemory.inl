//构造函数 
//**********************************************************************************************************************************************

template<typename T>
GSharedPtr<T>::GSharedPtr(value_pointer pVal)
{
	if (pVal == nullptr) 
	{
		val = nullptr;
		p_reference_count = nullptr;
	}
	else
	{
		p_reference_count = GNEW size_t(1);
		val = pVal;
	}
}

template<typename T>
GSharedPtr<T>::GSharedPtr(const GSharedPtr& ptr)
{
	if (ptr.val == nullptr)
	{
		val = nullptr;
		p_reference_count = nullptr;
	}
	else
	{
		p_reference_count = ptr.p_reference_count;
		//(*p_reference_count)++;
		GEngine::GSystem::GLockedIncrement((long*)p_reference_count);
		val = ptr.val;
	}
}

//析构函数
//**********************************************************************************************************************************************

template<typename T>
GSharedPtr<T>::~GSharedPtr()
{
	//(*p_reference_count)--;
	if (p_reference_count == nullptr)
		return;

	GEngine::GSystem::GLockedDecrement((long*)p_reference_count);
	if (*p_reference_count == 0)
	{
		GSAFE_DELETE(val);
		GSAFE_DELETE(p_reference_count);
	}
}

//成员函数
//**********************************************************************************************************************************************
template<typename T>
size_t GSharedPtr<T>::use_count()
{
	if (p_reference_count != nullptr)
		return *p_reference_count;
	else
		return 0;
}


//符号重载函数
//**********************************************************************************************************************************************

template<typename T>
GSharedPtr<T> GSharedPtr<T>::operator=(const GSharedPtr& rhs)
{
	if (p_reference_count != nullptr)
	{
		GEngine::GSystem::GLockedDecrement((long*)p_reference_count);
		if (*p_reference_count == 0)
		{
			GSAFE_DELETE(val);
			GSAFE_DELETE(p_reference_count);
		}
	}
	if (rhs.p_reference_count != nullptr)	
		GEngine::GSystem::GLockedIncrement((long*)rhs.p_reference_count);
	
	val = rhs.val;
	p_reference_count = rhs.p_reference_count;
	return *this;
}

template<typename T>
T& GSharedPtr<T>::operator*()
{
	return *val;
}

template<typename T>
T* GSharedPtr<T>::operator->()
{
	return val;
}