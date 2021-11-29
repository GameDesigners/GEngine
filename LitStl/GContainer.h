#ifndef GCONTAINER_H
#define GCONTAINER_H
#include <GMemManager.h>
#include "GStlMicro.h"
using namespace GEngine::GSystem;

namespace GEngine{
	namespace GStl{
        
		/*
		 *   ����ʽ������
		 *   array,vector,deque,list,forward_list
		 *   ʵ�ַ�ʽΪ�����顢����
		 *   
		 *   ����ʽ������
		 *   set,multiset,map,multimap
		 *   ʵ�ַ�ʽΪ��������
		 * 
		 *   ����������
		 *   unordered_set,unorder_multiset,unorder_map,unorder_multimap
		 *   ʵ�ַ�ʽΪ����ϣ��
		 * 
		 */


		/// <summary>
		/// ��������
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

						MMFun().Deallocate((char*)pAddr, 0, true);
					}
				}
			}

		protected:
			virtual bool empty() = 0;
			virtual size_t size() = 0;
			virtual size_t capcity() = 0;
			virtual void clear() = 0;
		};

		template<class T> class GSTL_API _Iterator  //Ĭ�ϵ�����
		{
		public:
			_Iterator() {}
			_Iterator(T* val) : current(val) {}
			~_Iterator() {}
			virtual const T* operator++() { return ++current; }     //ǰ��++
			virtual const T* operator++(int) { return current++; }  //����++��
			virtual const T* operator--() { return --current; }     //ǰ��--
			virtual const T* operator--(int) { return current--; }  //����--
			virtual T& operator*()  { return *current; }            //������
			virtual const T* operator+(size_t idx) { return current + idx; }
			virtual const T* operator-(size_t idx) { return current - idx; }
			virtual bool operator!=(const _Iterator& rhs)
			{
				return current != rhs.current;
			}
			virtual bool operator==(const _Iterator& rhs)
			{
				return current == rhs.current;
			}
		protected:
			T* current;
		};
		template<class T> class GSTL_API _CIterator  //����������
		{
		public:
			_CIterator() {}
			_CIterator(T* val) : current(val) {}
			~_CIterator() {}
			virtual const T* operator++() { return ++current; }     //ǰ��++
			virtual const T* operator++(int) { return current++; }  //����++��
			virtual const T* operator--() { return --current; }     //ǰ��--
			virtual const T* operator--(int) { return current--; }  //����--
			virtual T operator*() { return *current; } //������
			virtual const T* operator+(size_t idx) { return current + idx;}
			virtual const T* operator-(size_t idx) { return current - idx;}
			virtual bool operator!=(const _CIterator& rhs)
			{
				return current != rhs.current;
			}
			virtual bool operator==(const _CIterator& rhs)
			{
				return current == rhs.current;
			}
		protected:
			T* current;
		};
		template<class T> class GSTL_API _RIterator  //���������
		{
		public:
			_RIterator() {}
			_RIterator(T* val) : current(val) {}
			~_RIterator() {}
			virtual const T* operator++() { return --current; }     //ǰ��++
			virtual const T* operator++(int) { return current--; }  //����++��
			virtual const T* operator--() { return ++current; }     //ǰ��--
			virtual const T* operator--(int) { return current++; }  //����--
			virtual T& operator*() { return *current;}      //������
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

		protected:
			T* current;
		};
		template<class T> class GSTL_API _CRIterator  //������������
		{
		public:
			_CRIterator() {}
			_CRIterator(T* val) : current(val) {}
			~_CRIterator() {}
			virtual const T* operator++() { return --current; }     //ǰ��++
			virtual const T* operator++(int) { return current--; }  //����++��
			virtual const T* operator--() { return ++current; }     //ǰ��--
			virtual const T* operator--(int) { return current++; }  //����--
			virtual T operator*() { return *current; }      //������
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
		protected:
			T* current;
		};
	}
}


#endif // !GCONTAINER_H
