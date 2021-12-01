#ifndef GDEQUE_H
#define GDEQUE_H
#include "GContainer.h"
namespace GEngine {
	namespace GStl {
		template<class T, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GDeque : public GContainer<T, MMFun>
		{

		};
	}
}
#endif // !GDEQUE_H


