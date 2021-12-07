#ifndef GFORWARDLIST_H
#define GFORWARDLIST_H
#include "GContainer.h"
#include "GIterator.h"
namespace GEngine {
	namespace GStl {
		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API GForwardList : public GContainer<T,MMFun>
		{

		};

#include "GForwardList.inl"
	}
}
#endif // !GFORWARDLIST_H


