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


		template<class T,GMemManagerFun MMFun=GMemObject::GetMemManager>
		class GSTL_API GContainer : public GMemObject
		{
		protected:
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
		};

	}
}


#endif // !GCONTAINER_H
