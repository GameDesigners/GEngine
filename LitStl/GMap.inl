#include "GMap.h"
// 构造函数
//*************************************************************************

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::__GMap() {}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::__GMap(const __GMap& cv)
{
	node_pointer cv_root = cv.m_root;
	node_pointer temp = this->__minimum(cv_root);
	while (temp != nullptr)
	{
		this->__insert(temp->key,temp->value);
		temp = this->Successor(temp);
	}
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::__GMap(__GMap&& rv) noexcept
{
	this->m_root = rv.m_root;
	this->m_count = rv.m_count;
	rv.m_root = nullptr;
	rv.m_count = 0;
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::__GMap(iterator_type _begin, iterator_type _end)
{
	for (iterator_type p = _begin; p != _end; p++)
		insert((*p).first, (*p).second);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::__GMap(std::initializer_list<GPair<Key, Value>> values)
{
	for (auto p = values.begin(); p != values.end(); p++)
		insert(p->first, p->second);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::~__GMap()
{
	this->Destroy();
}


// 赋值函数
//*************************************************************************

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::operator=(const __GMap& cv)
{
	clear();
	node_pointer cv_root = cv.m_root;
	node_pointer cv_firste = this->__minimum(cv_root);
	iterator_type src_iter = _GMap_Iterator<Key,Value, Compare, MMFun>(cv_firste);
	iterator_type _end = _GMap_Iterator<Key, Value, Compare, MMFun>(nullptr);

	for (src_iter; src_iter != _end; src_iter++) 
	{
		auto pair = (*src_iter);
		insert(pair.first,pair.second);
	}
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::operator=(__GMap&& rv) noexcept
{
	if (rv.m_root == this->m_root)
		return;

	clear();
	this->m_root = rv.m_root;
	this->m_count = rv.m_count;
	rv.m_root = nullptr;
	rv.m_count = 0;
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::operator=(std::initializer_list<GPair<Key, Value>> values)
{
	clear();
	for (auto p = values.begin(); p != values.end(); p++)
		insert(p->first, p->second);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::swap(__GMap& v)
{
	size_t temp_count = v.m_count;
	node_pointer temp_root = v.m_root;

	v.m_count = this->m_count;
	v.m_root = this->m_root;

	this->m_count = temp_count;
	this->m_root = temp_root;
}



template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
Compare GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::key_comparator()
{
	return this->comparator;
}

// 访问函数
//*************************************************************************

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
Value& GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::operator[](const Key& key)
{
	node_pointer res = this->Search(key);
	if (res != nullptr)
		return res->value;

	node_pointer node = this->__insert(key, Value());
	return node->value;

}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
Value& GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::at(const Key& key)
{
	node_pointer res = this->Search(key);
	GASSERT(res != nullptr);
	return res->value;
}


//安插和移除
//*************************************************************************
template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
GPair<typename GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::iterator_type, bool> GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::insert(const Key& key, const Value& val)
{
	if (IsMulti)
	{
		node_pointer node = this->__insert(key, val);
		return GPair<iterator_type, bool>(_GMap_Iterator<Key, Value, Compare, MMFun>(node), true);
	}
	else
	{
		node_pointer res = this->Search(key);
		if (res != nullptr)
			return GPair<iterator_type, bool>(res, false);
		node_pointer node = this->__insert(key,val);
		return GPair<iterator_type, bool>(_GMap_Iterator<Key, Value, Compare, MMFun>(node), true);
	}
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::insert(iterator_type _begin, iterator_type _end)
{
	for (iterator_type p = _begin; p != _end; p++) 
	{
		auto pair = *p;
		insert(pair.first, pair.second);
	}
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::insert(std::initializer_list<GPair<Key, Value>> values)
{
	for (auto p = values.begin(); p != values.end(); p++)
		insert(p->first, p->second);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
template<typename ...Args>
inline GPair<typename __GMap<Key, Value, IsMulti, Compare, MMFun>::iterator_type, bool> __GMap<Key, Value, IsMulti, Compare, MMFun>::emplace(const Key&key,Args ...args)
{
	Value val(args...);
	return insert(key, val);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::earse(const Key& key)
{
	if (IsMulti)
	{
		node_pointer res = this->Search(key);
		while (res != nullptr)
		{
			this->__remove(this->m_root, res);
			res = this->Search(key);
		}
	}
	else
	{
		this->Remove(key);
	}
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::earse(iterator_type pos)
{
	node_pointer node = pos.current;
	if (node != nullptr) {
		this->__remove(this->m_root, node);
		pos.current = nullptr;
	}
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::earse(iterator_type _begin, iterator_type _end)
{
	iterator_type p = _begin;
	while (p != _end)
		this->__remove(this->m_root, (p++).current);
}


// 虚函数重写
//*************************************************************************

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::empty()
{
	return this->m_count == 0;
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
size_t GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::size()
{
	return this->m_count;
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
void GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::clear()
{
	this->Destroy();
}




//特殊的查找函数
//*************************************************************************
template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
inline size_t GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::count(const Key& key)
{
	if (IsMulti)
	{
		node_pointer res = this->Search(key);
		if (res == nullptr)
			return 0;
		size_t _count = 1;
		res = this->Successor(key);
		while (res != nullptr && res->key == key)
		{
			_count++;
			res = this->Successor(res);
		}
		return _count;
	}
	else
	{
		node_pointer res = this->Search(key);
		if (res == nullptr)
			return 0;
		else
			return 1;
	}
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
inline typename GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::iterator_type GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::find(const Key& key)
{
	node_pointer res = this->Search(key);
	return _GMap_Iterator<Key, Value, Compare, MMFun>(res);
}

//运算符重载
//*************************************************************************
template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool __GMap<Key, Value, IsMulti, Compare, MMFun>::operator==(const __GMap& rhs)
{
	if (rhs.m_count != this->m_count)
		return false;

	iterator_type lhs_iter = begin();
	node_pointer rhs_firste = this->__minimum(rhs.m_root);
	iterator_type rhs_iter = _GMap_Iterator<Key, Value, Compare, MMFun>(rhs_firste);
	iterator_type _end = _GMap_Iterator<Key, Value, Compare, MMFun>(nullptr);

	while (lhs_iter != _end && rhs_iter != _end)
	{
		if (lhs_iter.current->key != rhs_iter.current->key)
			return false;
		lhs_iter++;
		rhs_iter++;
	}
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::operator!=(const __GMap& rhs)
{
	iterator_type lhs_iter = begin();
	node_pointer rhs_firste = this->__minimum(rhs.m_root);
	iterator_type rhs_iter = _GMap_Iterator<Key, Value, Compare, MMFun>(rhs_firste);
	iterator_type _end = _GMap_Iterator<Key, Value, Compare, MMFun>(nullptr);

	while (lhs_iter != _end && rhs_iter != _end)
	{
		if (lhs_iter.current->key != rhs_iter.current->key)
			return true;
		lhs_iter++;
		rhs_iter++;
	}
	return lhs_iter != _end || rhs_iter != _end;
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
inline bool GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::operator<(const __GMap& rhs)
{
	iterator_type lhs_iter = begin();
	node_pointer rhs_firste = this->__minimum(rhs.m_root);
	iterator_type rhs_iter = _GMap_Iterator<Key, Value, Compare, MMFun>(rhs_firste);
	iterator_type _end = _GMap_Iterator<Key, Value, Compare, MMFun>(nullptr);

	while (lhs_iter != _end && rhs_iter != _end)
	{
		if (lhs_iter.current->key > rhs_iter.current->key)
			return false;
		lhs_iter++;
		rhs_iter++;
	}
	return rhs_iter != _end;
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::operator>(const __GMap& rhs)
{
	iterator_type lhs_iter = begin();
	node_pointer rhs_firste = this->__minimum(rhs.m_root);
	iterator_type rhs_iter = _GMap_Iterator<Key, Value, Compare, MMFun>(rhs_firste);
	iterator_type _end = _GMap_Iterator<Key, Value, Compare, MMFun>(nullptr);

	while (lhs_iter != _end && rhs_iter != _end)
	{
		if (lhs_iter.current->key < rhs_iter.current->key)
			return false;
		lhs_iter++;
		rhs_iter++;
	}
	return lhs_iter != _end;
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
bool GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::operator>=(const __GMap& rhs)
{
	return !(* this < rhs);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
inline bool GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::operator<=(const __GMap& rhs)
{
	return !(*this > rhs);
}




// 迭代器相关函数
//*************************************************************************

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::iterator_type GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::begin()
{
	node_pointer minmum = this->Minmum();
	return _GMap_Iterator<Key, Value, Compare, MMFun>(minmum);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::iterator_type GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::end()
{
	return _GMap_Iterator<Key, Value, Compare, MMFun>(nullptr);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::c_iterator_type GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::cbegin()
{
	node_pointer minmum = this->Minmum();
	return _GMap_CIterator<Key, Value, Compare, MMFun>(minmum);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::c_iterator_type GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::cend()
{
	return _GMap_CIterator<Key, Value, Compare, MMFun>(nullptr);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::r_iterator_type GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::rbegin()
{
	node_pointer maxmum = this->Maxmum();
	return _GMap_RIterator<Key, Value, Compare, MMFun>(maxmum);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::r_iterator_type GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::rend()
{
	return _GMap_RIterator<Key, Value, Compare, MMFun>(nullptr);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::cr_iterator_type GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::crbegin()
{
	node_pointer maxmum = this->Maxmum();
	return _GMap_CRIterator<Key, Value, Compare, MMFun>(maxmum);
}

template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun>
typename GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::cr_iterator_type GEngine::GStl::__GMap<Key, Value, IsMulti, Compare, MMFun>::crend()
{
	return _GMap_CRIterator<Key, Value, Compare, MMFun>(nullptr);
}