#ifndef GSET_H
#define GSET_H
#include "GBalanceTree.h"
#include "GAlgorithm.h"
#include "GIterator.h"
#include "GUtility.h"

namespace GEngine {
	namespace GStl {

		template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun> class GSTL_API __GSet;

		template<class T, typename Compare=less<T>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API _GSet_Iterator : public iterator<bidirectional_iterator_tag, T>
		{
			friend class __GSet<T, true, Compare, MMFun>;
			friend class __GSet<T, false, Compare, MMFun>;

		public:
			typedef bidirectional_iterator_tag        iterator_category;
			typedef ptrdiff_t                         distance;
			typedef T                                 value_type;
			typedef T*                                value_pointer;
			typedef T&                                value_reference;

			typedef __set_balance_tree_node<T, Compare,MMFun>* node_pointer;
			typedef _GSet_Iterator<T, Compare,MMFun>  self_type;

		public:
			_GSet_Iterator() : current(nullptr) {}
			_GSet_Iterator(node_pointer val) : current(val) {}
			_GSet_Iterator(const _GSet_Iterator& _itera) { current = _itera.current; }
			~_GSet_Iterator() {}
			void operator=(const _GSet_Iterator& _itera) { current = _itera.current; }

			self_type& operator++() { current = __get_successor(current); return *this; }
			self_type& operator--() { current = __get_predecessor(current); return *this; }
			self_type  operator++(int) { node_pointer temp = current; current = __get_successor(current); return _GSet_Iterator<T, Compare, MMFun>(temp); }
			self_type  operator--(int) { node_pointer temp = current; current = __get_predecessor(current); return _GSet_Iterator<T, Compare, MMFun>(temp); }
			T& operator*() { return current->key; }
			T* operator->() { return &current->key; }

			bool operator!=(const _GSet_Iterator& rhs) { return current != rhs.current; }
			bool operator==(const _GSet_Iterator& rhs) { return current == rhs.current; }

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

		template<class T, typename Compare = less<T>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API _GSet_CIterator : public iterator<bidirectional_iterator_tag, T>
		{
			friend class __GSet<T, true, Compare, MMFun>;
			friend class __GSet<T, false, Compare, MMFun>;

		public:
			typedef bidirectional_iterator_tag        iterator_category;
			typedef ptrdiff_t                         distance;
			typedef T                                 value_type;
			typedef T* value_pointer;
			typedef T& value_reference;

			typedef __set_balance_tree_node<T, Compare, MMFun>* node_pointer;
			typedef _GSet_CIterator<T, Compare, MMFun>  self_type;

		public:
			_GSet_CIterator() : current(nullptr) {}
			_GSet_CIterator(node_pointer val) : current(val) {}
			_GSet_CIterator(const _GSet_CIterator& _itera) { current = _itera.current; }
			~_GSet_CIterator() {}
			void operator=(const _GSet_CIterator& _itera) { current = _itera.current; }

			self_type& operator++() { current = __get_successor(current); return *this; }
			self_type& operator--() { current = __get_predecessor(current); return *this; }
			self_type  operator++(int) { node_pointer temp = current; current = __get_successor(current); return _GSet_CIterator<T, Compare, MMFun>(temp); }
			self_type  operator--(int) { node_pointer temp = current; current = __get_predecessor(current); return _GSet_CIterator<T, Compare, MMFun>(temp); }
			const T& operator*() { return current->key; }
			T* operator->() const{ return &current->key; } 

			bool operator!=(const _GSet_CIterator& rhs) { return current != rhs.current; }
			bool operator==(const _GSet_CIterator& rhs) { return current == rhs.current; }

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

		template<class T, typename Compare = less<T>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API _GSet_RIterator : public iterator<bidirectional_iterator_tag, T>
		{
			friend class __GSet<T, true, Compare, MMFun>;
			friend class __GSet<T, false, Compare, MMFun>;

		public:
			typedef bidirectional_iterator_tag        iterator_category;
			typedef ptrdiff_t                         distance;
			typedef T                                 value_type;
			typedef T* value_pointer;
			typedef T& value_reference;

			typedef __set_balance_tree_node<T, Compare, MMFun>* node_pointer;
			typedef _GSet_RIterator<T, Compare, MMFun>  self_type;

		public:
			_GSet_RIterator() : current(nullptr) {}
			_GSet_RIterator(node_pointer val) : current(val) {}
			_GSet_RIterator(const _GSet_RIterator& _itera) { current = _itera.current; }
			~_GSet_RIterator() {}
			void operator=(const _GSet_RIterator& _itera) { current = _itera.current; }

			self_type& operator++() { current = __get_predecessor(current); return *this; }
			self_type& operator--() { current = __get_successor(current); return *this; }
			self_type  operator++(int) { node_pointer temp = current; current = __get_predecessor(current); return _GSet_RIterator<T, Compare, MMFun>(temp); }
			self_type  operator--(int) { node_pointer temp = current; current = __get_successor(current); return _GSet_RIterator<T, Compare, MMFun>(temp); }
			T& operator*() { return current->key; }
			T* operator->(){ return &current->key; }

			bool operator!=(const _GSet_RIterator& rhs) { return current != rhs.current; }
			bool operator==(const _GSet_RIterator& rhs) { return current == rhs.current; }

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

		template<class T, typename Compare = less<T>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API _GSet_CRIterator : public iterator<bidirectional_iterator_tag, T>
		{
			friend class __GSet<T, true, Compare, MMFun>;
			friend class __GSet<T, false, Compare, MMFun>;

		public:
			typedef bidirectional_iterator_tag        iterator_category;
			typedef ptrdiff_t                         distance;
			typedef T                                 value_type;
			typedef T* value_pointer;
			typedef T& value_reference;

			typedef __set_balance_tree_node<T, Compare, MMFun>* node_pointer;
			typedef _GSet_CRIterator<T, Compare, MMFun>  self_type;

		public:
			_GSet_CRIterator() : current(nullptr) {}
			_GSet_CRIterator(node_pointer val) : current(val) {}
			_GSet_CRIterator(const _GSet_CRIterator& _itera) { current = _itera.current; }
			~_GSet_CRIterator() {}
			void operator=(const _GSet_CRIterator& _itera) { current = _itera.current; }

			self_type& operator++() { current = __get_predecessor(current); return *this; }
			self_type& operator--() { current = __get_successor(current); return *this; }
			self_type  operator++(int) { node_pointer temp = current; current = __get_predecessor(current); return _GSet_CRIterator<T, Compare, MMFun>(temp); }
			self_type  operator--(int) { node_pointer temp = current; current = __get_successor(current); return _GSet_CRIterator<T, Compare, MMFun>(temp); }
			const T& operator*() { return current->key; }
			T* operator->() const{ return &current->key; }

			bool operator!=(const _GSet_CRIterator& rhs) { return current != rhs.current; }
			bool operator==(const _GSet_CRIterator& rhs) { return current == rhs.current; }

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



		template<class T,bool IsMulti,typename Compare=less<T>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API __GSet : public __set_balance_tree<T, Compare, MMFun>
		{
		public:
			typedef _GSet_Iterator<T,Compare,MMFun>        iterator_type;
			typedef _GSet_CIterator<T,Compare,MMFun>       c_iterator_type;
			typedef _GSet_RIterator<T,Compare,MMFun>       r_iterator_type;
			typedef _GSet_CRIterator<T,Compare,MMFun>      cr_iterator_type;

			typedef __set_balance_tree_node<T, Compare, MMFun>* node_pointer;
			typedef Compare                           comparator_type;
		public:
			__GSet();
			__GSet(const __GSet& cv);
			__GSet(__GSet&& rv) noexcept;
			__GSet(iterator_type _begin, iterator_type _end);
			__GSet(std::initializer_list<T> values);
			~__GSet();

	    //赋值函数
		public:
			void operator=(const __GSet& cv);
			void operator=(__GSet&& rv) noexcept;
			void operator=(std::initializer_list<T> values);
			void swap(__GSet& v);

			Compare value_comparator();

		//安插和移除
		public:
			GPair<iterator_type,bool> insert(const T& val);
			//void insert(const iterator_type& pos, const T& val);
			void insert(iterator_type _begin, iterator_type _end);
			void insert(std::initializer_list<T> values);
			template<typename... Args> GPair<iterator_type, bool> emplace(Args... args);
			//template<typename... Args> void emplace(iterator_type pos, Args... args);
			void earse(const T& val);
			void earse(iterator_type pos);
			void earse(iterator_type _begin, iterator_type _end);

		//虚函数重写
		public:
			virtual bool empty();
			virtual size_t size();
			virtual void clear();

		//特殊的查找函数
		public:
			size_t count(const T& val);
			iterator_type find(const T& val);
			iterator_type lower_bound(const T& val);
			iterator_type upper_bound(const T& val);
			GPair<iterator_type, iterator_type> equal_range(const T& val);



		//运算符重载
		public:
			bool operator==(const __GSet& rhs);
			bool operator!=(const __GSet& rhs);
			bool operator<(const __GSet& rhs);
			bool operator>(const __GSet& rhs);
			bool operator>=(const __GSet& rhs);
			bool operator<=(const __GSet& rhs);

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


		private:
			virtual size_t capcity() { return 0; }
		};

		template<class T, typename Compare = less<T>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		using GSet = __GSet<T, false, Compare, MMFun>;

		template<class T, typename Compare = less<T>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		using GMultiSet = __GSet<T, true, Compare, MMFun>;

#include "GSet.inl"

	}
}
#endif // !GSET_H
