#ifndef GCONTAINER_H
#define GCONTAINER_H
#include <GMemManager.h>
#include "GStlMicro.h"
using namespace GEngine::GSystem;

namespace GEngine{
	namespace GStl{
        
		/*
		 *   ����ʽ����,ʵ�ַ�ʽΪ�����顢����
		 *   GArray        -->   |   GArray.h        |   GArray.inl        |   GArray.cpp         |   code review :
		 *   GVector       -->   |   GVector.h       |   GVector.inl       |   GVector.cpp		  |	  code review :
		 *   GDeque        -->   |   GDeque.h        |   GDeque.inl        |   GDeque.cpp		  |	  code review :
		 *   GList         -->   |   GList.h         |   GList.inl         |   GList.cpp		  |	  code review :2021.10.12
		 *   GForwardList  -->   |   GForwardList.h  |   GForwardList.inl  |   GForwardList.cpp	  |   code review :2021.10.12
		 * 
		 *  
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

		//placement ���캯��[placement new, ����T1::T1(value);���ܱ����ص�new��������]
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
