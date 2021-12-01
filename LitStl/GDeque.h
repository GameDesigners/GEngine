#ifndef GDEQUE_H
#define GDEQUE_H
#include "GContainer.h"
namespace GEngine {
	namespace GStl {
		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API GDeque : public GContainer<T, MMFun>
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

		public:
			typedef _Base_Iterator<T>       _base_iterator;

			enum
			{
				DefaultBufferSize=24,
			};

		private:
			//队列内存缓冲块
			template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
			class __deque_memory_buffer_block : public GContainer<T,MMFun>
			{
			public:
				__deque_memory_buffer_block()
				{
					m_data = this->New(DefaultBufferSize);
					GASSERT(m_data != nullptr);
					m_count = 0;
					m_constructed = 0;
				}

				~__deque_memory_buffer_block()
				{
					if (m_data != nullptr)
					{
						this->Delete(m_data, DefaultBufferSize, m_constructed);
						m_data = nullptr;
						m_count = 0;
						m_constructed = 0;
					}
				}

				void insert(T* pos);
				void remove(T* pos);
			private:
				T*      m_data;  //连续内存块
				size_t  m_count;
				size_t  m_constructed;
			};
		
		//构造函数
		public:
			GDeque();
			GDeque(const GDeque& cv);
			GDeque(GDeque&& rv);
			GDeque(size_t num);
			GDeque(size_t num,const T& val);
			GDeque(_base_iterator _begin, _base_iterator _end);
			GDeque(std::initializer_list<T> values);

		//赋值函数
			void operator=(const GDeque& cv);
			void operator=(GDeque&& rv);
			void operator=(std::initializer_list<T> values);

			void assign(size_t num, const T& val);
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
			size_t m_count;
		};

#include "GDeque.inl"
	}
}
#endif // !GDEQUE_H


