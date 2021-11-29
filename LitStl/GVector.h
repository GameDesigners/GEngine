#ifndef GVECTOR_H
#define GVECTOR_H
#include "GContainer.h"
namespace GEngine{
	namespace GStl {
		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GVector : public GContainer<T, MMFun>
		{
		public:
			typedef size_t           size_type;
			typedef T                value_type;
			typedef T&               reference;
			typedef const T&         const_reference;
			typedef T*               pointer;
			typedef const T*         const_pointer;
			typedef const T*         iterator;
			typedef T* const         const_iterator;

			typedef _Iterator<T>     iteractor_type;
			typedef _CIterator<T>    c_iterator_type;
			typedef _RIterator<T>    r_iterator_type;
			typedef _CRIterator<T>   cr_iterator_type;

			enum
			{
				DefaultCapcity = 24,
				IncreaseCapcityStep = 24
			};
		
		//构造函数
		public:
			GVector();
			GVector(const GVector& cv);
			GVector(GVector&& rv);
			GVector(size_t _capcity);
			GVector(size_t _count, const T& val);
			GVector(iterator begin, iterator end);
			GVector(std::initializer_list<T> values);
			~GVector();
		
        //赋值函数
		public:
			void operator=(const GVector& cv);
			void operator=(GVector&& rv);
			void operator=(std::initializer_list<T> values);

			void assign(int _count, const T& val);
			void assign(iterator begin, iterator end);
			void assign(std::initializer_list<T> values);
			void swap(GVector& v);

	    //访问函数
		public:
			T& operator[](size_t idx);
			T& at(size_t idx);
			T& front();
			T& back();

	    //安插和移除
		public:
			void push_back();
			void pop_back();
			void insert(iteractor_type pos, T val);
			void insert(interator_type pos, interator_type begin, interator_type end);
			void insert


	    //虚函数重写
		public:
			virtual bool empty();
			virtual size_t size();
			virtual size_t capcity();
			virtual void clear();

		//非更易型操作
		public:
			void reserve(size_t _capcity);
			void shrink_to_fit();

		//运算发重载
		public:
			bool operator==(const GVector& rhs);
			bool operator!=(const GVector& rhs);
			bool operator<(const GVector& rhs);
			bool operator>(const GVector& rhs);
			bool operator>=(const GVector& rhs);
			bool operator<=(const GVector& rhs);

		//迭代器
		public:
			iteractor_type   begin();
			iteractor_type   end();
			c_iterator_type  cbegin();
			c_iterator_type  cend();
			r_iterator_type  rbegin();
			r_iterator_type  rend();
			cr_iterator_type crbegin();
			cr_iterator_type crend();

		private:
			T*         m_data;
			size_t     m_count;
			size_t     m_capcity;
		};

#include "GVector.inl"
	}
}

#endif // !GVECTOR_H

