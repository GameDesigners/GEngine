#ifndef GDEQUE_H
#define GDEQUE_H
#include "GContainer.h"
namespace GEngine {
	namespace GStl {
		//向前声明
		template<class T, GMemManagerFun MMFun> class GSTL_API _Deque_Iterator;
		template<class T, GMemManagerFun MMFun> class __deque_memory_buffer_block;
		template<class T, GMemManagerFun MMFun> class GSTL_API GDeque;

		//队列内存缓冲块
		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class __deque_memory_buffer_block : public GContainer<T, MMFun>
		{
			friend class GDeque<T,MMFun>;
			typedef _Deque_Iterator<T, MMFun> _iterator_type;
		public:
			__deque_memory_buffer_block(size_t block_size);
			__deque_memory_buffer_block(const __deque_memory_buffer_block& cv);
			__deque_memory_buffer_block(__deque_memory_buffer_block&& rv);
			~__deque_memory_buffer_block();


			void assign(size_t _count);
			void assign(size_t _count, const T& val);

			void operator=(const __deque_memory_buffer_block& cv);
			void operator=(__deque_memory_buffer_block&& rv);

			_iterator_type insert(_iterator_type pos, const T& cv);
			void remove(_iterator_type pos);
			bool full();

		//虚函数重载
		public:
			virtual bool empty();
			virtual size_t size();
			virtual size_t capcity();
			virtual void clear();

		private:
			inline bool _vertify_iterator(_iterator_type& _iter)
			{
				return _iter._first==m_data && 
					   _iter._last==m_data+m_count&&
					   _iter._node==this;
			}
			inline void _construct_no_cv(size_t idx)
			{
				if (ValueBase<T>::NeedsConstructor)
				{
					if (idx < m_constructed)  //已经调用过构造函数
						return;
					construct(m_data + idx);
					m_constructed++;
				}
			}
			inline void _construct_idx(size_t idx,const T& cv)
			{
				if (ValueBase<T>::NeedsConstructor)
				{
					if (idx >= m_capcity)
						return;
					if (idx < m_constructed) {  //已经调用过构造函数
						*(m_data + idx) = cv;
						return;
					}
					construct(m_data + idx, cv);
					m_constructed++;
				}
				else
				{
					*(m_data + idx) = cv;
				}
			}
			inline void _destruct_idx(size_t idx)
			{
				if (ValueBase<T>::NeedsDestructor)
				{
					if (m_constructed > idx)
					{
						(m_data + idx)->~T();
						m_constructed--;
					}
				}
			}
		private:
			T*      m_data;
			size_t  m_count;
			size_t  m_capcity;
			size_t  m_constructed;
		};


		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API GDeque : public GContainer<__deque_memory_buffer_block<T,MMFun>*, MMFun>
		{
		public:
			typedef size_t                  size_type;
			typedef T                       value_type;
			typedef T&                      reference_type;
			typedef const T&                const_reference_type;
			typedef T*                      pointer;

			typedef _Vector_Iterator<T>     iterator_type;
			typedef _Vector_CIterator<T>    c_iterator_type;
			typedef _Vector_RIterator<T>    r_iterator_type;
			typedef _Vector_CRIterator<T>   cr_iterator_type;

			typedef __deque_memory_buffer_block<T,MMFun>* node_pointer;

		public:
			typedef _Base_Iterator<T>       _base_iterator;

			enum
			{
				DefaultBufferSize = 24,
				DefaultMapSize = 2,
				IncreaseMapCapcityStep=2
			};
			
		
		//构造函数
		public:
			GDeque();
			GDeque(const GDeque& cv);
			GDeque(GDeque&& rv);
			GDeque(size_t _count);
			GDeque(size_t _count, const T& val);
			GDeque(_base_iterator _begin, _base_iterator _end);
			GDeque(std::initializer_list<T> values);
			~GDeque();

		//赋值函数
		public:
			void operator=(const GDeque& cv);
			void operator=(GDeque&& rv);
			void operator=(std::initializer_list<T> values);

			void assign(size_t _count, const T& val);
			void assign(_base_iterator _begin, _base_iterator _end);
			void assign(std::initializer_list<T> values);
			void assign(const GDeque& cv);
			void swap(GDeque& deque);

		//访问函数
		public:
			T& operator[](size_t idx);
			T& at(size_t idx);
			T& front();
			T& back();

		//安插和移除
		public:
			void push_back(const T& cv);
			void push_back(T&& rv);
			void pop_back();
			void push_front(const T& cv);
			void push_front(T&& rv);
			void pop_front();
			_base_iterator insert(_base_iterator pos, const T& val);
			_base_iterator insert(_base_iterator pos, size_t num, const T& val);
			_base_iterator insert(_base_iterator pos, _base_iterator _begin, _base_iterator _end);
			_base_iterator insert(_base_iterator pos, std::initializer_list<T> values);
			template<class ...Args> _base_iterator emplace(_base_iterator pos, Args&&... args);
			template<class ...Args> void emplace_front(Args&... args);
			template<class ...Args> void emplace_back(Args&... args);
			_base_iterator erase(_base_iterator pos);
			_base_iterator erase(_base_iterator _begin, _base_iterator _end);
			void resize(size_t num);
			void resize(size_t num, const T& val);

		//虚函数重写
		public:
			virtual bool empty();
			virtual size_t size();
			virtual void clear();
		private:
			virtual size_t capcity() {  return 0; }  //不提供容量操作
			
		//非更易型操作
		public:
			void shrink_to_fit();

		//运算符重载
		public:
			bool operator==(const GDeque& rhs);
			bool operator!=(const GDeque& rhs);
			bool operator<(const GDeque& rhs);
			bool operator>(const GDeque& rhs);
			bool operator>=(const GDeque& rhs);
			bool operator<=(const GDeque& rhs);


		//迭代器
			//迭代器
		public:
			iterator_type   begin();
			iterator_type   end();
			c_iterator_type  cbegin();
			c_iterator_type  cend();
			r_iterator_type  rbegin();
			r_iterator_type  rend();
			cr_iterator_type crbegin();
			cr_iterator_type crend();

		private:
			inline void _create_new_buffer_block(size_t idx, size_t buffer_size=DefaultBufferSize)
			{
				if (idx < m_map_count || idx>m_map_capcity)  //目标地址已经指向一个缓冲区，不允许更换；不允许跨指针赋值
					return;
				if (m_map_count == m_map_capcity)            //map容量已经满了，需要重新分配map
					_remalloc_map();
				m_map[idx] = GNEW __deque_memory_buffer_block<T, MMFun>(buffer_size);
				GASSERT(m_map[idx] != nullptr);
				m_map_count++;
			}

			inline void _remalloc_map()
			{
				if (m_map != nullptr)
				{
					size_t new_capcity = m_map_capcity + IncreaseMapCapcityStep;
					node_pointer* new_map = this->New(new_capcity);
					GASSERT(new_map != nullptr);
					GMemoryCpy(
						new_map, 
						sizeof(__deque_memory_buffer_block<T, MMFun>*) * new_capcity, 
						m_map, 
						sizeof(__deque_memory_buffer_block<T, MMFun>*) * m_map_count
					); 
					this->Delete(m_map, m_map_capcity, 0);
					m_map_capcity = new_capcity;
				}
			}

		private:
			__deque_memory_buffer_block<T, MMFun>** m_map;
			size_t m_map_count;
			size_t m_map_capcity;
		};


		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API _Deque_Iterator
		{
			friend __deque_memory_buffer_block<T,MMFun>;
		public:
			typedef T                               value_type;
			typedef T&                              reference_type;
			typedef T*                              value_pointer;
			typedef const T&                        const_reference_type;
 			typedef __deque_memory_buffer_block<T>* node_pointer;

		public:
			_Deque_Iterator(T* cur, T* first, T* last, node_pointer node)
				: current(cur),
				_first(first), _last(last),
				_node(node){}

			virtual _Deque_Iterator<T, MMFun>& operator++();
			virtual _Deque_Iterator<T, MMFun>& operator--();
			virtual T& operator*();
			virtual T* operator->();

			virtual _Deque_Iterator<T, MMFun> operator++(int);
			virtual _Deque_Iterator<T, MMFun> operator--(int);
			virtual _Deque_Iterator<T, MMFun> operator+(int idx);
			virtual _Deque_Iterator<T, MMFun> operator-(int idx);

			virtual bool operator!=(const _Deque_Iterator& rhs);
			virtual bool operator==(const _Deque_Iterator& rhs);
			virtual int  operator-(const _Deque_Iterator& rhs);

		private:
			value_pointer current;   //迭代器当前指向的变量
			value_pointer _first;    
			value_pointer _last;
			node_pointer  _node;
		};

#include "GDeque.inl"
	}
}
#endif // !GDEQUE_H


