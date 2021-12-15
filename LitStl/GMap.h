#ifndef GMAP_H
#define GMAP_H
#include "GBalanceTree.h"
#include "GAlgorithm.h"
#include "GIterator.h"
#include "GUtility.h"

namespace GEngine {
	namespace GStl {
		template<class Key,class Value, typename Compare = less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API GMap : public __map_balance_tree<Key, Value, Compare, MMFun>
		{

		};

		template<class Key, class Value, typename Compare = less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API GMultiMap : public __map_balance_tree<Key, Value, Compare, MMFun>
		{

		};

#include "GMap.inl"
	}
}
#endif // !GMAP_H
