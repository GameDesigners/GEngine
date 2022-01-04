#ifndef GARRAY_H
#define GARRAY_H
#include "GContainer.h"
#include "GIterator.h"
namespace GEngine {
	namespace GStl {
		
		template<class T,size_t N>
		class GSTL_API GArray : public GContainer<T,GMemObject::GetMemManager>
		{
		public:
			typedef size_t           size_type;
			typedef T                value_type;
			typedef T&               reference;
			typedef const T&         const_reference;
			typedef T*               pointer;
			typedef const T*         const_pointer;

			typedef _SingleMemUnit_Iterator<T>     iterator_type;
			typedef _SingleMemUnit_CIterator<T>    c_iterator_type;
			typedef _SingleMemUnit_RIterator<T>    r_iterator_type;
			typedef _SingleMemUnit_CRIterator<T>   cr_iterator_type;

		//构造函数
		public:
			GArray();
			GArray(const GArray& cv);
			GArray(GArray&& rv);
			GArray(iterator_type _begin, iterator_type _end);
			GArray(std::initializer_list<T> values);
			~GArray();

		//赋值函数
		public:
			void operator=(const GArray& cv);
			void operator=(GArray&& rv);
			void operator=(std::initializer_list<T> values);
			void fill(const T& val);
			void swap(GArray& v);

		//访问函数
		public:
			T& operator[](int idx);
			T&  at(int idx);
			T&  front();
			T&  back();

		//虚函数重写
		public:
			virtual bool empty() const;
			virtual size_t size() const;
			virtual size_t capcity() const;
			virtual void clear();

		//运算符重载
		public:
			bool operator==(const GArray& rhs);
			bool operator!=(const GArray& rhs);
			bool operator<(const GArray& rhs);
			bool operator>(const GArray& rhs);
			bool operator>=(const GArray& rhs);
			bool operator<=(const GArray& rhs);

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
			T m_data[N] = {};
		};


#include "GArray.inl"
	}
}
#endif // !GARRAY_H