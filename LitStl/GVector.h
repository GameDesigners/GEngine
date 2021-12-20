#ifndef GVECTOR_H
#define GVECTOR_H
#include "GContainer.h"
#include "GIterator.h"
namespace GEngine{
	namespace GStl {
		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API GVector : public GContainer<T, MMFun>
		{
		public:
			typedef size_t                         size_type;
			typedef T                              value_type;
			typedef T&                             reference_type;
			typedef const T&                       const_reference_type;
			typedef T*                             pointer;

			typedef _SingleMemUnit_Iterator<T>     iterator_type;
			typedef _SingleMemUnit_CIterator<T>    c_iterator_type;
			typedef _SingleMemUnit_RIterator<T>    r_iterator_type;
			typedef _SingleMemUnit_CRIterator<T>   cr_iterator_type;

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
			GVector(size_t _count);
			GVector(size_t _count, const T& val);
			GVector(iterator_type _begin, iterator_type _end);
			GVector(std::initializer_list<T> values);
			~GVector();
		
        //赋值函数
		public:
			void operator=(const GVector& cv);
			void operator=(GVector&& rv);
			void operator=(std::initializer_list<T> values);

			void assign(int _count, const T& val);
			void assign(iterator_type begin, iterator_type end);
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
			void push_back(const T& cv);
			void push_back(T&& rv);
			void pop_back();
			iterator_type insert(iterator_type pos, const T& val);
			iterator_type insert(iterator_type pos, size_t num, const T& val);
			iterator_type insert(iterator_type pos, iterator_type _begin, iterator_type _end);
			iterator_type insert(iterator_type pos, std::initializer_list<T> values);
			template<class ...Args> iterator_type emplace(iterator_type pos, Args&&... args);
			template<class ...Args> iterator_type emplace_back(Args&&...args);
			iterator_type erase(iterator_type pos);
			iterator_type erase(iterator_type _begin, iterator_type _end);
			void resize(size_t num);
			void resize(size_t num, const T& val);
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

		//运算符重载
		public:
			bool operator==(const GVector& rhs);
			bool operator!=(const GVector& rhs);
			bool operator<(const GVector& rhs);
			bool operator>(const GVector& rhs);
			bool operator>=(const GVector& rhs);
			bool operator<=(const GVector& rhs);

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
			T*         m_data;
			size_t     m_count;
			size_t     m_capcity;
			size_t     m_constructed;

			inline size_t _caculate_increased_capcity(size_t target_count,size_t _old_capcity=DefaultCapcity)
			{
				while (_old_capcity <= target_count)
					_old_capcity += IncreaseCapcityStep;
				return _old_capcity;
			}
			inline void _construct_elem_no_cv(size_t index)
			{
				if (ValueBase<T>::NeedsConstructor)
				{
					if (index < m_constructed)  //已经调用过构造函数
						return;
					construct(m_data + index);
					m_constructed++;
				}
			}
			inline void _construct_elem(size_t index, const T& cv)
			{
				if (ValueBase<T>::NeedsConstructor) 
				{
					if (index < m_constructed) {  //已经调用过构造函数
						*(m_data + index) = cv;
						return;
					}
					construct(m_data + index, cv);
					m_constructed++;
				}
				else
				{
					*(m_data + index) = cv;
				}
			}
			inline void _construct_addr(T* addr, const T& cv)
			{
				if (ValueBase<T>::NeedsConstructor)
				{
					if ((addr-m_data) < m_constructed) {  //已经调用过构造函数
						*addr = cv;
						return;
					}
					construct(addr, cv);
					m_constructed++;
				}
				else
				{
					*addr = cv;
				}
			}
			inline void _construct_iterator(iterator_type itera, const T& cv)
			{
				_construct_elem(itera - begin(), cv);
			}
			inline void _destruct_elem(size_t index)
			{
				if (ValueBase<T>::NeedsDestructor)
				{
					if (m_constructed > index) 
					{
						(m_data+index)->~T();
						m_constructed--;
					}
				}
			}
			inline void _destruct_addr(T* addr)
			{
				if (addr == nullptr)
					return;
				if (ValueBase<T>::NeedsDestructor)
				{
					if ((addr - m_data) < m_constructed) 
					{
						addr->~T();
						m_constructed--;
					}
				}
			}
			inline void _new_data_memory_addr(size_t new_capcity, bool _is_copy_old_data)
			{
				T* new_memory = this->New(new_capcity);
				GASSERT(new_memory != nullptr);
				m_capcity = new_capcity;
				size_t old_need_destructed = m_constructed;
				if (_is_copy_old_data)//复制容器旧数据	
				{
					for(int index=0;index<m_count;index++)
					{
						construct(new_memory + index);
						*(new_memory + index) = g_move(*(m_data + index));
					}
					m_constructed = m_count;
				}
				else 
				{
					m_count = 0;
					m_constructed = 0;//清除已构造对象数量（因为无复制旧的内存）
				}
				this->Delete(m_data, m_capcity, old_need_destructed);
				m_data = new_memory;
			}
		};

#include "GVector.inl"
	}
}

#endif // !GVECTOR_H

