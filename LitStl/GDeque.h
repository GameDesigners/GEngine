#ifndef GDEQUE_H
#define GDEQUE_H
#include "GContainer.h"
#include "GIterator.h"
namespace GEngine {
	namespace GStl {
		//��ǰ����
		template<class T, GMemManagerFun MMFun> class GSTL_API GDeque;

		/// <summary>
		/// ��ȡdequeʹ�õ�Buffer��С��Ԫ�ظ�����
		/// 1.��n��=0,��ζ��ָ���û��Զ���buffer��С
		/// 2.Ĭ����ȡ512��С�����ɵ�Ԫ�ظ�����sizeof(T��> 512,��Buffer Count=1
		/// </summary>
		/// <param name="n">�Ƿ��Զ��壨0ΪĬ�ϣ�</param>
		/// <param name="sz">T��size</param>
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
			
		
		//���캯��
		public:
			GDeque() {}
			GDeque(const GDeque& cv);
			GDeque(GDeque&& rv);
			GDeque(size_t _count);
			GDeque(size_t _count, const T& val);
			GDeque(iterator_type _begin, iterator_type _end);
			GDeque(std::initializer_list<T> values);
			~GDeque() {}

		//��ֵ����
		public:
			void operator=(const GDeque& cv);
			void operator=(GDeque&& rv);
			void operator=(std::initializer_list<T> values);

			void assign(size_t _count, const T& val);
			void assign(iterator_type _begin, iterator_type _end);
			void assign(std::initializer_list<T> values);
			void assign(const GDeque& cv);
			void swap(GDeque& deque);

		//���ʺ���
		public:
			T& operator[](size_t idx);
			T& at(size_t idx);
			T& front();
			T& back();

		//������Ƴ�
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

		//�麯����д
		public:
			virtual bool empty() const { return true; }
			virtual size_t size() const { return 0; }
			virtual void clear();
		private:
			virtual size_t capcity() const {  return 0; }  //���ṩ��������
			
		//�Ǹ����Ͳ���
		public:
			void shrink_to_fit();

		//���������
		public:
			bool operator==(const GDeque& rhs);
			bool operator!=(const GDeque& rhs);
			bool operator<(const GDeque& rhs);
			bool operator>(const GDeque& rhs);
			bool operator>=(const GDeque& rhs);
			bool operator<=(const GDeque& rhs);


		//������
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


