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
			inline void Delete(T* pAddr,int Num,int ConstructsNum)
			{
				if (pAddr != nullptr)
				{
					if (ConstructsNum > 0)
					{
						if (ValueBase<T>::NeedsDestructor)
						{
							for (int i = 0; i < ConstructsNum; i++)
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

		template<class T> class GSTL_API _Base_Iterator  //默认迭代器
		{
		public:
			_Base_Iterator(T* val) : current(val) {}
			~_Base_Iterator() {}
			virtual void operator=(const _Base_Iterator& _itera) { current = _itera.current; } //拷贝构造函数

			virtual _Base_Iterator& operator++() { ++current; return *this; }               //前置++
			virtual _Base_Iterator& operator--() { --current; return *this; }               //前置--
			virtual T& operator*() { return *current; }                                   //解引用
			virtual T* operator->() { return current; }                                   //指针访问

			virtual _Base_Iterator operator++(int) { T* temp = current; current++; return _Base_Iterator(temp); }  //后置++(非重载版本)
			virtual _Base_Iterator operator--(int) { T* temp = current; current--; return _Base_Iterator(temp); }  //后置--(非重载版本)
			virtual _Base_Iterator operator+(int idx) { return _Base_Iterator(current + idx); }
			virtual _Base_Iterator operator-(int idx) { return _Base_Iterator(current - idx); }

			virtual bool operator!=(const _Base_Iterator& rhs) { return current != rhs.current; }
			virtual bool operator==(const _Base_Iterator& rhs) { return current == rhs.current; }
			virtual int  operator-(const _Base_Iterator& rhs) { return this->current - rhs.current; }

		protected:
			T* current;
		};
		template<class T> class GSTL_API _Base_CIterator  //常量迭代器
		{
		public:
			_Base_CIterator(T* val) : current(val) {}
			~_Base_CIterator() {}
			virtual void operator=(const _Base_CIterator& _citera) { current = _citera.current; } //拷贝构造函数

			virtual _Base_CIterator& operator++() { ++current; return *this; }               //前置++
			virtual _Base_CIterator& operator--() { --current; return *this; }               //前置--
			virtual const T&  operator*() { return *current; }                                     //解引用
			virtual T* operator->() { return current; }                                     //指针访问

			virtual _Base_CIterator operator++(int) { T* temp = current; current++; return _Base_CIterator(temp); }  //后置++(非重载版本)
			virtual _Base_CIterator operator--(int) { T* temp = current; current--; return _Base_CIterator(temp); }  //后置--(非重载版本)
			virtual _Base_CIterator operator+(int idx) { return _Base_CIterator(current + idx); }
			virtual _Base_CIterator operator-(int idx) { return _Base_CIterator(current - idx); }

			virtual bool operator!=(const _Base_CIterator& rhs) { return current != rhs.current; }
			virtual bool operator==(const _Base_CIterator& rhs) { return current == rhs.current; }
			virtual int  operator-(const _Base_CIterator& rhs) { return this->current - rhs.current; }
		protected:
			T* current;
		};
		template<class T> class GSTL_API _Base_RIterator  //反向迭代器
		{
		public:
			_Base_RIterator(T* val) : current(val) {}
			~_Base_RIterator() {}
			virtual void operator=(const _Base_RIterator& _ritera) { current = _ritera.current; } //拷贝构造函数

			virtual _Base_RIterator& operator++() { --current; return *this; }               //前置++
			virtual _Base_RIterator& operator--() { ++current; return *this; }               //前置--
			virtual T&  operator*() { return *current; }                                   //解引用
			virtual T* operator->() { return current; }                                   //指针访问

			virtual _Base_RIterator operator++(int) { T* temp = current; current--; return _Base_RIterator(temp); }  //后置++(非重载版本)
			virtual _Base_RIterator operator--(int) { T* temp = current; current++; return _Base_RIterator(temp); }  //后置--(非重载版本)
			virtual _Base_RIterator operator+(int idx) { return _Base_RIterator(current - idx); }
			virtual _Base_RIterator operator-(int idx) { return _Base_RIterator(current + idx); }

			virtual bool operator!=(const _Base_RIterator& rhs) { return current != rhs.current; }
			virtual bool operator==(const _Base_RIterator& rhs) { return current == rhs.current; }
			virtual int  operator-(const _Base_RIterator& rhs) { return this->current - rhs.current; }
		protected:
			T* current;
		};
		template<class T> class GSTL_API _Base_CRIterator  //反向常量迭代器
		{
		public:
			_Base_CRIterator(T* val) : current(val) {}
			~_Base_CRIterator() {}
			virtual void operator=(const _Base_CRIterator& _critera) { current = _critera.current; } //拷贝构造函数

			virtual _Base_CRIterator& operator++() { --current; return *this; }               //前置++
			virtual _Base_CRIterator& operator--() { ++current; return *this; }               //前置--
			virtual const T& operator*() { return *current; }                                     //解引用
			virtual T* operator->() { return current; }                                     //指针访问

			virtual _Base_CRIterator operator++(int) { T* temp = current; current--; return _Base_CRIterator(temp); }  //后置++(非重载版本)
			virtual _Base_CRIterator operator--(int) { T* temp = current; current++; return _Base_CRIterator(temp); }  //后置--(非重载版本)
			virtual _Base_CRIterator operator+(int idx) { return _Base_CRIterator(current - idx); }
			virtual _Base_CRIterator operator-(int idx) { return _Base_CRIterator(current + idx); }

			virtual bool operator!=(const _Base_CRIterator rhs) { return current != rhs.current; }
			virtual bool operator==(const _Base_CRIterator rhs) { return current == rhs.current; }
			virtual int  operator-(const _Base_CRIterator& rhs) { return this->current - rhs.current; }
		protected:
			T* current;
		};

		template<class T> class GSTL_API _Vector_Iterator : public _Base_Iterator<T>
		{
		public:
			_Vector_Iterator(T* t) : _Base_Iterator<T>(t) {}
		};
		template<class T> class GSTL_API _Vector_CIterator : public _Base_CIterator<T>
		{
		public:
		public:
			_Vector_CIterator(T* t) : _Base_CIterator<T>(t) {}
		};
		template<class T> class GSTL_API _Vector_RIterator : public _Base_RIterator<T>
		{
		public:
			_Vector_RIterator(T* t) : _Base_RIterator<T>(t) {}
		};
		template<class T> class GSTL_API _Vector_CRIterator : public _Base_CRIterator<T>
		{
		public:
			_Vector_CRIterator(T* t) : _Base_CRIterator<T>(t) {}
		};


		//placement 构造函数[placement new, 调用T1::T1(value);不能被重载的new方法！！]
		template<class T1, class T2>
		inline void construct(T1* p, const T2& value)
		{
			GNEW(p)T1(value);
		}

		template<class T>
		inline void construct(T* p)
		{
			GNEW(p)T();
		}
	}
}


#endif // !GCONTAINER_H
