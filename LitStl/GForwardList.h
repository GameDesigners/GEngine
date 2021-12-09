#ifndef GFORWARDLIST_H
#define GFORWARDLIST_H
#include "GContainer.h"
#include "GIterator.h"
namespace GEngine {
	namespace GStl {
		template<class T, GMemManagerFun MMFun> class GSTL_API GForwardList;

		template<class T> struct __forward_list_node
		{
			T value;
			__forward_list_node* next = nullptr;
		};

		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API _Forward_List_Iterator : public iterator<bidirectional_iterator_tag, __forward_list_node<T>>
		{
			friend class GForwardList<T, MMFun>;

		public:
			typedef bidirectional_iterator_tag        iterator_category;
			typedef T                                 value_type;
			typedef T* value_pointer;
			typedef T& value_reference;

			typedef __forward_list_node<T>*           node_pointer;
			typedef _Forward_List_Iterator<T, MMFun>  self_type;


		public:
			_Forward_List_Iterator(__forward_list_node<T>* val) : current(val) {}
			_Forward_List_Iterator(const _Forward_List_Iterator& itera) { current = itera.current; }
			~_Forward_List_Iterator() {}
			void operator=(const _Forward_List_Iterator& _itera) { current = _itera.current; }

			self_type& operator++() { current = current->next; return *this; }
			self_type  operator++(int) { node_pointer temp = current; current = current->next; return _Forward_List_Iterator<T, MMFun>(temp); }  //后置++(非重载版本)

			T& operator*() { return current->value; }                                               //解引用
			T* operator->() { return &(operator*()); }

			bool operator!=(const _Forward_List_Iterator& rhs) { return current != rhs.current; }
			bool operator==(const _Forward_List_Iterator& rhs) { return current == rhs.current; }

		private:
			__forward_list_node<T>* current;
		};

		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API _Forward_List_CIterator : public iterator<bidirectional_iterator_tag, __forward_list_node<T>>
		{
			friend class GForwardList<T, MMFun>;

		public:
			typedef bidirectional_iterator_tag        iterator_category;
			typedef T                                 value_type;
			typedef T* value_pointer;
			typedef T& value_reference;

			typedef __forward_list_node<T>* node_pointer;
			typedef _Forward_List_CIterator<T, MMFun>  self_type;


		public:
			_Forward_List_CIterator(__forward_list_node<T>* val) : current(val) {}
			_Forward_List_CIterator(const _Forward_List_CIterator& itera) { current = itera.current; }
			~_Forward_List_CIterator() {}
			void operator=(const _Forward_List_CIterator& _itera) { current = _itera.current; }

			self_type& operator++() { current = current->next; return *this; }
			self_type  operator++(int) { node_pointer temp = current; current = current->next; return _Forward_List_CIterator<T, MMFun>(temp); }  //后置++(非重载版本)

			const T& operator*() { return current->value; }                                               //解引用
			T* operator->() { return &(operator*()); }

			bool operator!=(const _Forward_List_CIterator& rhs) { return current != rhs.current; }
			bool operator==(const _Forward_List_CIterator& rhs) { return current == rhs.current; }

		private:
			__forward_list_node<T>* current;
		};

		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API GForwardList : public GContainer<__forward_list_node<T>,MMFun>
		{
		public:
			typedef size_t                             size_type;
			typedef T                                  value_type;
			typedef T&                                 reference_type;
			typedef const T&                           const_reference_type;
			typedef T*                                 pointer;
												       
			typedef __forward_list_node<T>*            node_pointer;

			typedef _Forward_List_Iterator<T, MMFun>   iterator_type;
			typedef _Forward_List_CIterator<T,MMFun>   c_iterator_type;


		//构造函数
		public:
			GForwardList();
			GForwardList(const GForwardList& cv);
			GForwardList(GForwardList&& rv);
			GForwardList(size_t _count);
			GForwardList(size_t _count, const T& val);
			GForwardList(iterator_type _begin, iterator_type _end);
			GForwardList(std::initializer_list<T> values);
			~GForwardList();

		//赋值函数
		public:
			void operator=(const GForwardList& cv);
			void operator=(GForwardList&& rv);
			void operator=(std::initializer_list<T> values);

			void assign(size_t _count, const T& val);
			void assign(iterator_type _begin, iterator_type _end);
			void assign(std::initializer_list<T> values);
			void swap(GForwardList& forward_list);

		//访问函数
		public:
			T& front();

		//安插和移除
		public:
			void push_front(const T& val);
			void pop_front();
			iterator_type insert_after(iterator_type pos, const T& val);
			iterator_type insert_after(iterator_type pos, size_t _count, const T& val);
			iterator_type insert_after(iterator_type pos, iterator_type _begin, iterator_type _end);
			iterator_type insert_after(iterator_type pos, std::initializer_list<T> values);
			template<class ...Args> void emplace_after(iterator_type pos, Args ...args);
			template<class ...Args> void emplace_front(Args ...args);
			void erase_after(iterator_type pos);
			void erase_after(iterator_type _begin, iterator_type _end);
			void remove(const T& val);
			template<class Operator> void remove_if(Operator op);
			void resize(size_t _count);
			void resize(size_t _count,const T& cv);

		//特殊更易型操作
			void unique();
			template<class Operator> void unique(Operator op);
			void splice_after(iterator_type pos, GForwardList& v);
			void splice_after(iterator_type pos, GForwardList& v, iterator_type splice_target);
			void splice_after(iterator_type pos, GForwardList& v, iterator_type _begin, iterator_type _end);
			void sort();
			template<class Operator> void sort(Operator op);
			void merge(const GForwardList& cv);
			template<class Operator> void merge(const GForwardList& cv, Operator op);
			void reverse();
			
		//虚函数重写
		public:
			virtual bool empty();
			virtual void clear();

		//运算符重载
		public:
			bool operator==(const GForwardList& rhs);
			bool operator!=(const GForwardList& rhs);
			bool operator<(const GForwardList& rhs);
			bool operator>(const GForwardList& rhs);
			bool operator>=(const GForwardList& rhs);
			bool operator<=(const GForwardList& rhs);

		//迭代器相关函数
		public:
			iterator_type    begin();
			iterator_type    end();
			c_iterator_type  cbegin();
			c_iterator_type  cend();

		protected:
			class Equals
			{
			public:
				Equals() {}
				Equals(const T& _comp) : comp(_comp) {}
				bool operator()(const T& elem)
				{
					return comp == elem;
				}

				bool operator()(const T& val1, const T& val2)
				{
					return val1 == val2;
				}
			private:
				T comp;
			};
		private:
			virtual size_t size() { return 0; };
			virtual size_t capcity() { return 0; };

			inline node_pointer __new_forwardlist_node(const T& val)
			{
				node_pointer p = this->New(1);
				GASSERT(p != nullptr);
				construct(&p->value, val);
				return p;
			}
			inline void delete_after(node_pointer node)
			{
				while (node != nullptr)
				{
					node_pointer temp = node->next;
					this->Delete(node, 1, 1);
					node = temp;
				}
			}

		private:
			node_pointer m_head;
		};

#include "GForwardList.inl"
	}
}
#endif // !GFORWARDLIST_H


