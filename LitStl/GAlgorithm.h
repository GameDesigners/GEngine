#ifndef GALGORITHM_H
#define GALGORITHM_H
#include "GStlMicro.h"
#include "GContainer.h"
namespace GEngine {
	namespace GStl {

		template<typename T>
		GSTL_API inline T accumulate(_Iterator<T> begin, _Iterator<T> end, T init)
		{
			for (auto p = begin; p != end; p++)
				init += *p;
			return init;
		}


		template<typename T,class Operation>
		GSTL_API inline void transform(_Iterator<T> begin, _Iterator<T> end, Operation op)
		{
			for (auto p = begin; p != end; p++)
				op(*p);
		}

		//取反函数对象
		template<typename T>
		struct negate
		{
			void operator()(T& val) {
				val = -val;
			}
		};
	}
}

#endif // !GALGORITHM_H
