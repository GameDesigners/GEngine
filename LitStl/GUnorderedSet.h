#ifndef GUNORDERED_SET_H
#define GUNORDERED_SET_H
#include "GHashTable.h"
namespace GEngine {
	namespace GStl {

		template<class Key, class Value, typename Compare = less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API GUnorderedSet
		{

		};
	}
}

#endif // !GUNORDERED_SET_H
