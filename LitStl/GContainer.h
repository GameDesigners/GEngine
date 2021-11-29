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
