// ���캯��
//*************************************************************************

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::GSet() {}

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::GSet(const GSet& cv)
{
	node_pointer temp = cv.m_root;
	while (temp != nullptr)
	{
		this->__insert(temp->key);
		temp = this->Successor(temp);
	}
}

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::GSet(GSet&& rv) noexcept
{
	this->m_root = rv.m_root;
	this->m_count = rv.m_count;
	rv.m_root = nullptr;
	rv.m_count = 0;
}

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::GSet(iterator_type _begin, iterator_type _end)
{
	for (auto p = _begin; p != _end; p++)
		this->__insert(*p);
}

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::GSet(std::initializer_list<T> values)
{
	for (auto p = values.begin(); p != values.end(); p++)
		this->__insert(*p);
}

template<class T, typename Compare, GMemManagerFun MMFun>
GSet<T, Compare, MMFun>::~GSet()
{
	this->Destroy();
}

//��ֵ����
//*************************************************************************
template<class T, typename Compare, GMemManagerFun MMFun>
void GSet<T, Compare, MMFun>::operator=(const GSet& cv)
{
	if()
}

template<class T, typename Compare, GMemManagerFun MMFun>
Compare GSet<T, Compare, MMFun>::value_comparator()
{
	return this->comparator;
}

//������Ƴ�
//*************************************************************************

template<class T, typename Compare, GMemManagerFun MMFun>
void GSet<T, Compare, MMFun>::insert(const T& val)
{
	this->__insert(val);
}



// �麯����д
//*************************************************************************

template<class T, typename Compare, GMemManagerFun MMFun>
bool GSet<T, Compare, MMFun>::empty()
{
	return this->m_count == 0;
}

template<class T, typename Compare, GMemManagerFun MMFun>
size_t GSet<T, Compare, MMFun>::size()
{
	return this->m_count;
}

template<class T, typename Compare, GMemManagerFun MMFun>
void GSet<T, Compare, MMFun>::clear()
{
	this->Destroy();
}