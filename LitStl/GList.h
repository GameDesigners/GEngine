#ifndef GLIST_H
#define GLIST_H
#include "GContainer.h"
#include "GIterator.h"

namespace GEngine {
	namespace GStl {
		template<class T, GMemManagerFun MMFun> class GSTL_API GList;

		template<class T> struct __list_node
		{
			T value;
			__list_node* prev = nullptr;
			__list_node* next = nullptr;
		};

		template<class T,GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API _List_Iterator : public iterator<bidirectional_iterator_tag, __list_node<T>>
		{
			friend class GList<T, MMFun>;
		public:
			typedef bidirectional_iterator_tag      iterator_category;
			typedef ptrdiff_t                       distance;
			typedef T                               value_type;
			typedef T* value_pointer;
			typedef T& value_reference;

			typedef __list_node<T>*                 node_pointer;
			typedef _List_Iterator<T, MMFun>        self_type;

		public:
			_List_Iterator() :current(nullptr) {}
			_List_Iterator(__list_node<T>* val) : current(val) {}
			_List_Iterator(const _List_Iterator& _itera) { current = _itera.current; }
			~_List_Iterator() {}
			void operator=(const _List_Iterator& _itera) { current = _itera.current; }

			self_type& operator++() { current = current->next; return *this; }                  //前置++
			self_type& operator--() { current = current->prev; return *this; }                  //前置--
			self_type  operator++(int) { node_pointer temp = current; current=current->next; return _List_Iterator<T, MMFun>(temp); }  //后置++(非重载版本)
			self_type  operator--(int) { node_pointer temp = current; current=current->prev; return _List_Iterator<T, MMFun>(temp); }  //后置--(非重载版本)
			T& operator*() { return current->value; }                                               //解引用
			T* operator->() { return &(operator*()); }                                              //指针访问

			bool operator!=(const _List_Iterator& rhs) { return current != rhs.current; }
			bool operator==(const _List_Iterator& rhs) { return current == rhs.current; }

		protected:
			__list_node<T>* current;
		};

		template<class T,GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API GList : public GContainer<__list_node<T>, MMFun>
		{
		public:
			typedef size_t                         size_type;
			typedef T                              value_type;
			typedef T&                             reference_type;
			typedef const T&                       const_reference_type;
			typedef T*                             pointer;

			typedef __list_node<T>*                node_pointer;

			typedef _List_Iterator<T,MMFun>        iterator_type;
			typedef _SingleMemUnit_CIterator<T>    c_iterator_type;
			typedef _SingleMemUnit_RIterator<T>    r_iterator_type;
			typedef _SingleMemUnit_CRIterator<T>   cr_iterator_type;

		public:
			GList();
			GList(const GList& cv);
			GList(GList&& rv);
			GList(size_t _count);
			GList(size_t _count, const T& val);
			GList(iterator_type _begin, iterator_type _end);
			GList(std::initializer_list<T> values);
			~GList();

		//赋值函数
		public:
			void operator=(const GList& cv);
			void operator=(GList&& rv);
			void operator=(std::initializer_list<T> values);

			void assign(size_t _count, const T& val);
			void assign(iterator_type _begin, iterator_type _end);
			void assign(std::initializer_list<T> values);
			void swap(GList& list);

		//访问函数
		public:
			T& front();
			T& back();

		//安插和移除
		public:
			void push_back(const T& val);
			void pop_back();
			void push_front(const T& val);
			void pop_front();
			iterator_type insert(iterator_type pos, const T& val);
			iterator_type insert(iterator_type pos, size_t _count, const T& val);
			iterator_type insert(iterator_type pos, iterator_type _begin, iterator_type _end);
			iterator_type insert(iterator_type pos, std::initializer_list<T> values);
			template<class ...Args> iterator_type emplace(iterator_type pos, Args... args);
			template<class ...Args> void emplace_back(Args... args);
			template<class ...Args> void emplace_front(Args... args);
			iterator_type erase(iterator_type pos);
			iterator_type erase(iterator_type _begin, iterator_type _end);
			void remove(const T& val);
			template<class OP> void remove_if(OP op);
			void resize(size_t _count);


		//虚函数重写
		public:
			virtual bool empty();
			virtual size_t size();
			virtual void clear();

		//运算符重载
		public:
			bool operator==(const GList& rhs);
			bool operator!=(const GList& rhs);
			bool operator<(const GList& rhs);
			bool operator>(const GList& rhs);
			bool operator>=(const GList& rhs);
			bool operator<=(const GList& rhs);

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

		protected:

		private:
			virtual size_t capcity() { return 0; }

			class Equals
			{
				Equals(const T& _comp) : comp(_comp) {}
				bool operator()(const T& elem)
				{
					return elem == comp;
				}
			private:
				T comp;
			};
		private:
			node_pointer  m_head;
			node_pointer  m_tail;
			size_t        m_count;
 		};

#include "GList.inl"
	}
}
#endif // !GLIST_H

