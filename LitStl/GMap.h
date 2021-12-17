#ifndef GMAP_H
#define GMAP_H
#include "GBalanceTree.h"
#include "GAlgorithm.h"
#include "GIterator.h"
#include "GUtility.h"

namespace GEngine {
	namespace GStl {

		template<class Key, class Value, bool IsMulti, typename Compare, GMemManagerFun MMFun> class __GMap;


		template<class Key, class Value, typename Compare = less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API _GMap_Iterator : public iterator<bidirectional_iterator_tag, Value>
		{
			friend class __GMap<Key, Value, true, Compare, MMFun>;
			friend class __GMap<Key, Value, false, Compare, MMFun>;

		public:
			typedef bidirectional_iterator_tag      iterator_category;
			typedef ptrdiff_t                       distance;

			typedef Key                             key_type;
			typedef Key* key_pointer;
			typedef Key& key_reference;

			typedef Value                           value_type;
			typedef Value* value_pointer;
			typedef Value& value_reference;

			typedef __map_balance_tree_node<Key, Value, Compare, MMFun>* node_pointer;
			typedef _GMap_Iterator<Key, Value, Compare, MMFun>  self_type;

		public:
			_GMap_Iterator() : current(nullptr) {}
			_GMap_Iterator(node_pointer val) : current(val) {}
			_GMap_Iterator(const _GMap_Iterator& _itera) { current = _itera.current; }
			~_GMap_Iterator() {}
			void operator=(const _GMap_Iterator& _itera) { current = _itera.current; }

			self_type& operator++() { current = __get_successor(current); return *this; }
			self_type& operator--() { current = __get_predecessor(current); return *this; }
			self_type  operator++(int) { node_pointer temp = current; current = __get_successor(current); return _GMap_Iterator<Key, Value, Compare, MMFun>(temp); }
			self_type  operator--(int) { node_pointer temp = current; current = __get_predecessor(current); return _GMap_Iterator<Key, Value, Compare, MMFun>(temp); }
			GPair<Key, Value> operator*() { return GPair<Key, Value>(current->key, current->value); }
			Value* operator->() { return &current->value; }

			bool operator!=(const _GMap_Iterator& rhs) { return current != rhs.current; }
			bool operator==(const _GMap_Iterator& rhs) { return current == rhs.current; }

		protected:
			node_pointer __get_successor(node_pointer node)  //获取后继节点
			{
				node_pointer temp = node;
				if (temp->right != nullptr)
				{
					temp = temp->right;
					while (temp->left != nullptr)
						temp = temp->left;
					return temp;
				}

				node_pointer parent = temp->parent;
				while (parent != nullptr && temp == parent->right)
				{
					temp = parent;
					parent = parent->parent;
				}
				return parent;
			}
			node_pointer __get_predecessor(node_pointer node)
			{
				node_pointer temp = node;
				if (temp->left != nullptr)
				{
					//在左子树中寻找最大的节点
					temp = temp->left;
					while (temp->left != nullptr)
						temp = temp->left;
					return temp;
				}
				node_pointer parent = temp->parent;
				while (parent != nullptr && temp == parent->left)
				{
					temp = parent;
					parent = parent->parent;
				}
				return parent;
			}
			node_pointer current;
		};

		template<class Key, class Value, typename Compare = less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		using _GMap_CIterator = _GMap_Iterator<Key, Value, Compare, MMFun>;

		template<class Key, class Value, typename Compare = less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API _GMap_RIterator : public iterator<bidirectional_iterator_tag, Value>
		{
			friend class __GMap<Key, Value, true, Compare, MMFun>;
			friend class __GMap<Key, Value, false, Compare, MMFun>;

		public:
		public:
			typedef bidirectional_iterator_tag      iterator_category;
			typedef ptrdiff_t                       distance;

			typedef Key                             key_type;
			typedef Key* key_pointer;
			typedef Key& key_reference;

			typedef Value                           value_type;
			typedef Value* value_pointer;
			typedef Value& value_reference;

			typedef __map_balance_tree_node<Key, Value, Compare, MMFun>* node_pointer;
			typedef _GMap_Iterator<Key, Value, Compare, MMFun>  self_type;

		public:
			_GMap_RIterator() : current(nullptr) {}
			_GMap_RIterator(node_pointer val) : current(val) {}
			_GMap_RIterator(const _GMap_RIterator& _itera) { current = _itera.current; }
			~_GMap_RIterator() {}
			void operator=(const _GMap_RIterator& _itera) { current = _itera.current; }

			self_type& operator++() { current = __get_predecessor(current); return *this; }
			self_type& operator--() { current = __get_successor(current); return *this; }
			self_type  operator++(int) { node_pointer temp = current; current = __get_predecessor(current); return _GMap_RIterator<Key, Value, Compare, MMFun>(temp); }
			self_type  operator--(int) { node_pointer temp = current; current = __get_successor(current); return _GMap_RIterator<Key, Value, Compare, MMFun>(temp); }
			GPair<Key, Value> operator*() { return GPair<Key, Value>(current->key, current->value); }
			Value* operator->() { return &current->value; }

			bool operator!=(const _GMap_RIterator& rhs) { return current != rhs.current; }
			bool operator==(const _GMap_RIterator& rhs) { return current == rhs.current; }

		protected:
			node_pointer __get_successor(node_pointer node)  //获取后继节点
			{
				node_pointer temp = node;
				if (temp->right != nullptr)
				{
					temp = temp->right;
					while (temp->left != nullptr)
						temp = temp->left;
					return temp;
				}

				node_pointer parent = temp->parent;
				while (parent != nullptr && temp == parent->right)
				{
					temp = parent;
					parent = parent->parent;
				}
				return parent;
			}
			node_pointer __get_predecessor(node_pointer node)
			{
				node_pointer temp = node;
				if (temp->left != nullptr)
				{
					//在左子树中寻找最大的节点
					temp = temp->left;
					while (temp->left != nullptr)
						temp = temp->left;
					return temp;
				}
				node_pointer parent = temp->parent;
				while (parent != nullptr && temp == parent->left)
				{
					temp = parent;
					parent = parent->parent;
				}
				return parent;
			}

			node_pointer current;
		};

		template<class Key, class Value, typename Compare = less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		using _GMap_CRIterator = _GMap_RIterator<Key, Value, Compare, MMFun>;

		template<class Key, class Value, bool IsMulti, typename Compare = less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API __GMap : public __map_balance_tree<Key, Value, Compare, MMFun>
		{
		public:
			typedef _GMap_Iterator<Key, Value, Compare, MMFun>        iterator_type;
			typedef _GMap_RIterator<Key, Value, Compare, MMFun>       c_iterator_type;
			typedef _GMap_RIterator<Key, Value, Compare, MMFun>       r_iterator_type;
			typedef _GMap_CRIterator<Key, Value, Compare, MMFun>      cr_iterator_type;

			typedef __map_balance_tree_node<Key, Value, Compare, MMFun>* node_pointer;
			typedef Compare                           comparator_type;

		public:
			__GMap();
			__GMap(const __GMap& cv);
			__GMap(__GMap&& rv) noexcept;
			__GMap(iterator_type _begin, iterator_type _end);
			__GMap(std::initializer_list<GPair<Key, Value>> values);
			~__GMap();

		//赋值函数
		public:
			void operator=(const __GMap& cv);
			void operator=(__GMap&& rv) noexcept;
			void operator=(std::initializer_list<GPair<Key, Value>> values);
			void swap(__GMap& v);

			Compare key_comparator();

		//访问函数
		public:
			Value& operator[](const Key& key);
			Value& at(const Key& key);

		//安插和移除
		public:
			GPair<iterator_type, bool> insert(const Key& key, const Value& val);
			//void insert(const iterator_type& pos, const T& val);
			void insert(iterator_type _begin, iterator_type _end);
			void insert(std::initializer_list<GPair<Key, Value>> values);
			template<typename... Args> GPair<iterator_type, bool> emplace(const Key& key, Args... args);
			//template<typename... Args> void emplace(iterator_type pos, Args... args);
			void earse(const Key& key);
			void earse(iterator_type pos);
			void earse(iterator_type _begin, iterator_type _end);

		//虚函数重写
		public:
			virtual bool empty();
			virtual size_t size();
			virtual void clear();

		//特殊的查找函数
		public:
			size_t count(const Key& key);
			iterator_type find(const Key& key);
			iterator_type lower_bound(const Key& key);
			iterator_type upper_bound(const Key& key);
			GPair<iterator_type, iterator_type> equal_range(const Key& key);


		//运算符重载
		public:
			bool operator==(const __GMap& rhs);
			bool operator!=(const __GMap& rhs);
			bool operator<(const __GMap& rhs);
			bool operator>(const __GMap& rhs);
			bool operator>=(const __GMap& rhs);
			bool operator<=(const __GMap& rhs);



		//迭代器相关函数
		public:
			iterator_type    begin();
			iterator_type    end();
			c_iterator_type  cbegin();
			c_iterator_type  cend();
			r_iterator_type  rbegin();
			r_iterator_type  rend();
			cr_iterator_type crbegin();
			cr_iterator_type crend();
		};

		template<class Key, class Value, typename Compare = less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		using GMap = __GMap<Key, Value, false, Compare, MMFun>;

		template<class Key, class Value, typename Compare = less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		using GMultiMap = __GMap<Key, Value, true, Compare, MMFun>;


#include "GMap.inl"

    }
}
#endif // !GMAP_H
