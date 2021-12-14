#ifndef GALGORITHM_H
#define GALGORITHM_H
#include "GStlMicro.h"
#include "GContainer.h"
#include "GIterator.h"
namespace GEngine {
	namespace GStl {

		template<typename Iterator>
		inline typename Iterator::value_type accumulate(Iterator begin, Iterator end, typename Iterator::value_type init)
		{
			while (begin != end)
			{
				init += *begin;
				advance(begin, 1);
			}
			return init;
		}

		template<typename Iterator, class Operation>
		inline void transform(Iterator begin, Iterator end, Operation op)
		{
			while (begin != end)
			{
				op(*begin);
				advance(begin, 1);
			}
		}

		//取反函数对象
		template<typename T>
		struct negate
		{
			void operator()(T& val) {
				val = -val;
			}
		};

		//小于的对象函数
		template<class T>
		class GSTL_API less
		{
		public:
			inline bool operator()(T& val1, T& val2)
			{
				return val1 < val2;
			}
		};
	}
}

#endif // !GALGORITHM_H
