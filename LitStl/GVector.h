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

			enum
			{
				DefaultCapcity = 24,
				IncreaseCapcityStep = 24
			};
		
		//构造函数
		public:
			constexpr GVector();
			constexpr GVector(const GVector& clone);
			constexpr GVector(GVector&& rv) noexcept;
			explicit  GVector(size_type count);
			constexpr GVector(size_type count, const_reference val);
			constexpr GVector(iterator_type first, iterator_type last);
			constexpr GVector(std::initializer_list<T> values);
			~GVector();
		
        //赋值函数
		public:
			constexpr GVector& operator=(const GVector& clone);
			constexpr GVector& operator=(GVector&& rv);
			constexpr GVector& operator=(std::initializer_list<T> values);

			constexpr void assign(int count, const_reference value);
			constexpr void assign(iterator_type first, iterator_type last);
			constexpr void assign(std::initializer_list<T> values);
			void swap(GVector& v);

	    //访问函数
		public:
			constexpr reference operator[](size_type idx);
			constexpr reference at(size_type idx);
			constexpr reference front();
			constexpr reference back();
			constexpr pointer   data() noexcept;

			constexpr const_reference operator[](size_type idx) const;
			constexpr const_reference at(size_type idx) const;
			constexpr const_reference front() const;
			constexpr const_reference back() const;
			constexpr const_pointer   data() const;

	    //安插和移除
		public:
			constexpr void push_back(const_reference cr);
			constexpr void push_back(T&& rv);
			constexpr void pop_back();
			constexpr iterator_type insert(iterator_type pos, const_reference value);
			constexpr iterator_type insert(iterator_type pos, T&& rv);
			constexpr iterator_type insert(iterator_type pos, size_type count, const_reference value);
			constexpr iterator_type insert(iterator_type pos, iterator_type first, iterator_type last);
			constexpr iterator_type insert(iterator_type pos, std::initializer_list<T> values);
			template<class ...Args> iterator_type emplace(iterator_type pos, Args&&... args);
			template<class ...Args> iterator_type emplace_back(Args&&...args);
			constexpr iterator_type erase(iterator_type pos);
			constexpr iterator_type erase(iterator_type first, iterator_type last);
			constexpr void resize(size_type count);
			constexpr void resize(size_type count, const_reference value);
	    //虚函数重写
		public:
			constexpr virtual bool empty() const;
			constexpr virtual size_t size() const;
			constexpr virtual size_t capcity() const;
			virtual void clear();

		//非更易型操作
		public:
			constexpr void reserve(size_type new_cap);
			constexpr void shrink_to_fit();

		//运算符重载
		public:
			bool operator==(const GVector& rhs) const;
			bool operator!=(const GVector& rhs) const;
			bool operator<(const GVector& rhs) const;
			bool operator>(const GVector& rhs) const;
			bool operator>=(const GVector& rhs) const;
			bool operator<=(const GVector& rhs) const;

		//迭代器
		public:
			iterator_type    begin();
			iterator_type    end();
			c_iterator_type  cbegin();
			c_iterator_type  cend();
			r_iterator_type  rbegin();
			r_iterator_type  rend();
			cr_iterator_type crbegin();
			cr_iterator_type crend();

		private:
			value_type* m_data;
			size_type   m_count;
			size_type   m_capcity;
			size_type   m_constructed;

			inline size_type __caculate_increased_capcity(size_type target_count, size_type old_capcity = DefaultCapcity)
			{
				while (old_capcity <= target_count)
					old_capcity += IncreaseCapcityStep;
				return old_capcity;
			}

			inline void __construct_elem_to_default_value(size_t index)
			{
				if (ValueBase<T>::NeedsConstructor)
				{
					if (index < m_constructed)  //已经调用过构造函数
						return;
					construct(m_data + index);
					m_constructed++;
				}
			}

			inline void __construct_element_idx(size_t index, const T& cv)
			{
				if (ValueBase<T>::NeedsConstructor) 
				{
					if (index < m_constructed) 
					{  
						//已经调用过构造函数
						*(m_data + index) = cv;
						return;
					}
					construct(m_data + index, cv);
					m_constructed++;
				}
				else
				{
					*(m_data + index) = cv;
					m_constructed++;
				}
			}

			inline void __construct_element_addr(T* addr, const T& cv)
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
			inline void __construct_element_iterator(iterator_type itera, const T& cv)
			{
				__construct_element_idx(itera - begin(), cv);
			}

			inline void __destruct_elem_idx(size_t index)
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
			inline void __destruct_elem_addr(T* addr)
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
			inline void __rellocate_memory_block(size_t new_capcity, bool is_copy_old_data)
			{
				T* new_memory = this->New(new_capcity);
				GASSERT(new_memory != nullptr);
				m_capcity = new_capcity;
				size_t old_need_destructed = m_constructed;
				if (is_copy_old_data)//复制容器旧数据	
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

