#ifndef GDEQUE_H
#define GDEQUE_H
#include "GContainer.h"
#include "GIterator.h"
namespace GEngine {
	namespace GStl {
		//向前声明
		template<class T, GMemManagerFun MMFun> class GSTL_API GDeque;

		/// <summary>
		/// 获取deque使用的Buffer大小（元素个数）
		/// 1.若n！=0,意味这指定用户自定义buffer大小
		/// 2.默认则取512大小能容纳的元素个数，sizeof(T）> 512,则Buffer Count=1
		/// </summary>
		/// <param name="n">是否自定义（0为默认）</param>
		/// <param name="sz">T的size</param>
		/// <returns></returns>
		inline size_t __deque_buf_size(size_t n, size_t elemSize)
		{
			return n != 0 ? n : (elemSize < 512 ? size_t(512 / elemSize) : size_t(1));
		}





		template<class T,size_t BufferSize=0>
		class GSTL_API _Deque_Iterator : public iterator<random_access_iterator_tag, T>
		{
		public:
			typedef random_access_iterator_tag      iterator_category;
			typedef ptrdiff_t                       distance;
			typedef T                               value_type;
			typedef T*                              value_pointer;
			typedef T&                              value_reference;
			typedef T**                             map_pointer;

			typedef _Deque_Iterator<T, BufferSize>   self_type;


		private:
			static size_t buffer_size() { return __deque_buf_size(BufferSize, sizeof(T)); }
			value_pointer cur;
			value_pointer first;
			value_pointer last;
			map_pointer   node;

		};


		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API GDeque : public GContainer<T, MMFun>
		{
		public:
			template<class T>
			struct __elements_buffer
			{
				T* _first;
				T* _last;
				T* _begin;
				T* _end;
			};

		public:
			typedef T                              value_type;
			typedef size_t                         size_type;
			typedef ptrdiff_t                      difference_type;
			typedef value_type&                    reference;
			typedef const value_type&              const_reference;
			typedef value_type*                    pointer;
			typedef const value_type*              const_pointer;
			typedef _SingleMemUnit_Iterator<T>     iterator_type;
			typedef _SingleMemUnit_CIterator<T>    c_iterator_type;
			typedef _SingleMemUnit_RIterator<T>    r_iterator_type;
			typedef _SingleMemUnit_CRIterator<T>   cr_iterator_type;

			typedef value_type**                   map_pointer;

			enum
			{
				DefaultBufferSize = 12,
				DefaultMapSize = 2,
				IncreaseMapCapcityStep=2
			};
			
		
		//构造函数
		public:
			GDeque() {}
			GDeque(const GDeque& cv);
			GDeque(GDeque&& rv);
			GDeque(size_t _count);
			GDeque(size_t _count, const T& val);
			GDeque(iterator_type _begin, iterator_type _end);
			GDeque(std::initializer_list<T> values);
			~GDeque() {}

		//赋值函数
		public:
			void operator=(const GDeque& cv);
			void operator=(GDeque&& rv);
			void operator=(std::initializer_list<T> values);

			void assign(size_t _count, const T& val);
			void assign(iterator_type _begin, iterator_type _end);
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
			iterator_type insert(iterator_type pos, const T& val);
			iterator_type insert(iterator_type pos, size_t num, const T& val);
			iterator_type insert(iterator_type pos, iterator_type _begin, iterator_type _end);
			iterator_type insert(iterator_type pos, std::initializer_list<T> values);
			template<class ...Args> iterator_type emplace(iterator_type pos, Args&&... args);
			template<class ...Args> void emplace_front(Args&... args);
			template<class ...Args> void emplace_back(Args&... args);
			iterator_type erase(iterator_type pos);
			iterator_type erase(iterator_type _begin, iterator_type _end);
			void resize(size_t num);
			void resize(size_t num, const T& val);

		//虚函数重写
		public:
			virtual bool empty() const { return true; }
			virtual size_t size() const { return 0; }
			virtual void clear();
		private:
			virtual size_t capcity() const {  return 0; }  //不提供容量操作
			
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
			

		private:
			map_pointer   m_map;
			size_type     map_size;
		};
#include "GDeque.inl"
	}
}
#endif // !GDEQUE_H


