#ifndef GARRAY_H
#define GARRAY_H
#include "GContainer.h"
#include "GIterator.h"
namespace GEngine {
	namespace GStl {
		
		template<class T,size_t N>
		class GSTL_API GArray : public GContainer<T,GMemObject::GetMemManager>
		{
		//成员类型
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

		//构造函数
		public:
			GArray();
			GArray(const GArray& clone);
			GArray(GArray&& rv);
			GArray(iterator_type begin_iterator, iterator_type end_iterator);
			GArray(std::initializer_list<T> values);
			~GArray();

		//赋值函数
		public:
			void operator=(const GArray& clone);
			void operator=(GArray&& rv);
			void operator=(std::initializer_list<T> values);
			void fill(const T& value);
			void swap(GArray& array);

		//访问函数
		public:
			constexpr reference operator[](size_type idx);
			constexpr reference at(size_type idx);
			constexpr reference front();
			constexpr reference back();

			constexpr const_reference operator[](size_type idx) const;
			constexpr const_reference at(size_type idx) const;
			constexpr const_reference front() const;
			constexpr const_reference back() const;

			constexpr pointer data() noexcept;
			constexpr const_pointer data() const noexcept;
		//虚函数重写
		public:
			constexpr virtual bool empty() const;
			constexpr virtual size_t size() const;
			constexpr virtual size_t capcity() const;
			virtual void clear();

		//运算符重载
		public:
			bool operator==(const GArray& rhs) const;
			bool operator!=(const GArray& rhs) const;
			bool operator<(const GArray& rhs) const;
			bool operator>(const GArray& rhs) const;
			bool operator>=(const GArray& rhs) const;
			bool operator<=(const GArray& rhs) const;

		//迭代器
		public:
			constexpr iterator_type    begin();
			constexpr iterator_type    end();
			constexpr c_iterator_type  cbegin();
			constexpr c_iterator_type  cend();
			constexpr r_iterator_type  rbegin();
			constexpr r_iterator_type  rend();
			constexpr cr_iterator_type crbegin();
			constexpr cr_iterator_type crend();


		private:
			value_type m_data[N] = {};
		};
#include "GArray.inl"
	}
}
#endif // !GARRAY_H