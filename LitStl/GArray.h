#ifndef GARRAY_H
#define GARRAY_H
#include "GContainer.h"
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
			typedef _Iterator<T>     iteractor_type;
			typedef _CIterator<T>    c_iterator_type;
			typedef _RIterator<T>    r_iterator_type;
			typedef _CRIterator<T>   cr_iterator_type;

		//���캯��
		public:
			GArray();
			GArray(const GArray& cv);
			GArray(GArray&& rv);
			GArray(iteractor_type _begin, iteractor_type _end);
			GArray(std::initializer_list<T> values);
			~GArray();

		//��ֵ����
		public:
			void operator=(const GArray& cv);
			void operator=(GArray&& rv);
			void operator=(std::initializer_list<T> values);
			void fill(const T& val);
			void swap(GArray& v);

		//���ʺ���
		public:
			T& operator[](int idx);
			T&  at(int idx);
			T&  front();
			T&  back();

		//�麯����д
		public:
			virtual bool empty();
			virtual size_t size();
			virtual size_t capcity();
			virtual void clear();

		//���������
		public:
			bool operator==(const GArray& rhs);
			bool operator!=(const GArray& rhs);
			bool operator<(const GArray& rhs);
			bool operator>(const GArray& rhs);
			bool operator>=(const GArray& rhs);
			bool operator<=(const GArray& rhs);

		//������
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
			T m_data[N] = {};
		};


#include "GArray.inl"
	}
}
#endif // !GARRAY_H