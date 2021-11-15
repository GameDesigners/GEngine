//���캯�� 
//*************************************************************************

template<typename T>
GSharedPtr<T>::GSharedPtr(value_pointer pVal)
{
	if (pVal == nullptr) 
	{
		p_reference_count = GNEW size_t(0);
		val = nullptr;
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
	p_reference_count = ptr.p_reference_count;
	(*p_reference_count)++;
	val = ptr.val;
}

//template<typename T>
//GSharedPtr<T>::GSharedPtr(GSharedPtr&& ptr) noexcept
//{
//	val = ptr.val;
//	p_reference_count = ptr.p_reference_count;
//	ptr.val = nullptr;
//}

//��������
//*************************************************************************

template<typename T>
GSharedPtr<T>::~GSharedPtr()
{
	(*p_reference_count)--;
	if (*p_reference_count == 0)
	{
		if (val != nullptr) {
			GDELETE val;
		}
	}
}

//��Ա����
//*************************************************************************
template<typename T>
size_t GSharedPtr<T>::use_count()
{
	return *p_reference_count;
}


//�������غ���
//*************************************************************************

template<typename T>
T& GSharedPtr<T>::operator=(const GSharedPtr& rhs)
{
	(*p_reference_count)++;//���ü��� +1
	return GSharedPtr(rhs.val, rhs.p_reference_count);
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