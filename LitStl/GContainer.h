#ifndef GCONTAINER_H
#define GCONTAINER_H
#include <GMemManager.h>
#include "GStlMicro.h"
using namespace GEngine::GSystem;

namespace GEngine{
	namespace GStl{
        
		/*
		 *   序列式容器：
		 *   array,vector,deque,list,forward_list
		 *   实现方式为：数组、链表
		 *   
		 *   关联式容器：
		 *   set,multiset,map,multimap
		 *   实现方式为：二叉树
		 * 
		 *   无序容器：
		 *   unordered_set,unorder_multiset,unorder_map,unorder_multimap
		 *   实现方式为：哈希表
		 * 
		 */


		/// <summary>
		/// 容器基类
		/// </summary>
		/// <typeparam name="T"></typeparam>
		template<class T,GMemManagerFun MMFun=GMemObject::GetMemManager>
		class GSTL_API GContainer : public GMemObject
		{
		public:
			
		protected:
			GContainer() {};
			~GContainer() {}

			inline T* New(size_t Num)
			{
				if (Num < 0)
					return nullptr;
				T* newAddr = (T*)MMFun().Allocate(sizeof(T) * Num, 0, true);
				GASSERT(newAddr != nullptr);
				/*if (ValueBase<T>::NeedsConstructor)
				{
					for (size_t idx = 0; idx < Num; idx++)
						GNEW(newAddr + idx)T;
				}*/
				return newAddr;
			}
			inline void Delete(T* pAddr,int Num)
			{
				if (pAddr != nullptr)
				{
					if (Num > 0)
					{
						if (ValueBase<T>::NeedsDestructor)
						{
							for (int i = 0; i < Num; i++)
								(pAddr + i)->~T();
						}
					}
					MMFun().Deallocate((char*)pAddr, 0, true);
					pAddr = nullptr;
				}
			}

		protected:
			virtual bool empty() = 0;
			virtual size_t size() = 0;
			virtual size_t capcity() = 0;
			virtual void clear() = 0;
		};

		template<class T> class GSTL_API _Iterator  //默认迭代器
		{
		public:
			_Iterator() {}
			_Iterator(T* val) : current(val) {}
			~_Iterator() {}
			virtual const _Iterator<T> operator++() { ++current; return _Iterator(current); }     //前置++
			virtual const _Iterator<T> operator++(int) { T* temp = current; current++; return _Iterator(temp); }  //后置++、
			virtual const _Iterator<T> operator--() { --current; return _Iterator(current); }     //前置--
			virtual const _Iterator<T> operator--(int) { T* temp = current; current--; return _Iterator(temp); }  //后置--
			virtual T& operator*()  { return *current; }            //解引用
			virtual const _Iterator<T> operator+(int idx) { return _Iterator(current + idx); }
			virtual const _Iterator<T> operator-(int idx) { return _Iterator(current - idx); }
			virtual bool operator!=(const _Iterator& rhs)
			{
				return current != rhs.current;
			}
			virtual bool operator==(const _Iterator& rhs)
			{
				return current == rhs.current;
			}
			virtual T* operator->() { return current; }
		protected:
			T* current;
		};
		template<class T> class GSTL_API _CIterator  //常量迭代器
		{
		public:
			_CIterator() {}
			_CIterator(T* val) : current(val) {}
			~_CIterator() {}
			virtual const T* operator++() { return ++current; }     //前置++
			virtual const T* operator++(int) { return current++; }  //后置++、
			virtual const T* operator--() { return --current; }     //前置--
			virtual const T* operator--(int) { return current--; }  //后置--
			virtual T operator*() { return *current; } //解引用
			virtual const _CIterator<T> operator+(size_t idx) { return _CIterator(current + idx); }
			virtual const _CIterator<T> operator-(size_t idx) { return _CIterator(current - idx); }
			virtual bool operator!=(const _CIterator& rhs)
			{
				return current != rhs.current;
			}
			virtual bool operator==(const _CIterator& rhs)
			{
				return current == rhs.current;
			}

			virtual T* operator->() { return current; }
		protected:
			T* current;
		};
		template<class T> class GSTL_API _RIterator  //反向迭代器
		{
		public:
			_RIterator() {}
			_RIterator(T* val) : current(val) {}
			~_RIterator() {}
			virtual const T* operator++() { return --current; }     //前置++
			virtual const T* operator++(int) { return current--; }  //后置++、
			virtual const T* operator--() { return ++current; }     //前置--
			virtual const T* operator--(int) { return current++; }  //后置--
			virtual T& operator*() { return *current;}      //解引用
			virtual const T* operator+(size_t idx) { return current - idx; }
			virtual const T* operator-(size_t idx) { return current + idx; }
			virtual bool operator!=(const _RIterator& rhs)
			{
				return current != rhs.current;
			}
			virtual bool operator==(const _RIterator& rhs)
			{
				return current == rhs.current;
			}
			virtual T* operator->() { return current; }
		protected:
			T* current;
		};
		template<class T> class GSTL_API _CRIterator  //反向常量迭代器
		{
		public:
			_CRIterator() {}
			_CRIterator(T* val) : current(val) {}
			~_CRIterator() {}
			virtual const T* operator++() { return --current; }     //前置++
			virtual const T* operator++(int) { return current--; }  //后置++、
			virtual const T* operator--() { return ++current; }     //前置--
			virtual const T* operator--(int) { return current++; }  //后置--
			virtual T operator*() { return *current; }      //解引用
			virtual const T* operator+(size_t idx) { return current - idx; }
			virtual const T* operator-(size_t idx) { return current + idx; }
			virtual bool operator!=(const _CRIterator& rhs)
			{
				return current != rhs.current;
			}
			virtual bool operator==(const _CRIterator& rhs)
			{
				return current == rhs.current;
			}
			virtual T* operator->() { return current; }
		protected:
			T* current;
		};

		template<class T> class GSTL_API _Vector_Iterator : public _Iterator<T>
		{
		public:
			_Vector_Iterator(T* t)
			{
				this->current = t;
			}
			virtual size_t operator-(const _Vector_Iterator& rhs)
			{
				return this->current - rhs.current;
			}
		};
		template<class T> class GSTL_API _Vector_CIterator : public _CIterator<T>
		{
		public:
			virtual size_t operator-(const _Vector_CIterator& rhs)
			{
				return this->current - rhs.current;
			}
		};
		template<class T> class GSTL_API _Vector_RIterator : public _RIterator<T>
		{
		public:
			virtual size_t operator-(const _Vector_RIterator& rhs)
			{
				return this->current - rhs.current;
			}
		};
		template<class T> class GSTL_API _Vector_CRIterator : public _CRIterator<T>
		{
		public:
			virtual size_t operator-(const _Vector_CRIterator& rhs)
			{
				return this->current - rhs.current;
			}
		};


		//placement 构造函数
		template<class T1, class T2>
		inline void construct(T1* p, const T2& value)
		{
			GNEW(p)T1(value);    //placement new, 调用T1::T1(value);不能被重载的new方法！！
		}
	}
}


#endif // !GCONTAINER_H
