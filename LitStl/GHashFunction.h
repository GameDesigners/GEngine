#ifndef GHASH_FUNCTION_H
#define GHASH_FUNCTION_H

namespace GEngine {
	namespace GStl {
        #define HASH_FUNC_TEMPLATE_TITLE template<>

		template<class T> struct __hash_function {};

		//偏特化（引擎自定义类型的哈希值计算对象函数）
		//*************************************************************************


		HASH_FUNC_TEMPLATE_TITLE struct __hash_function<int>
		{
			int operator()(const int& val,const int& capcity) const
			{
				return val;
			}
		};

		HASH_FUNC_TEMPLATE_TITLE struct __hash_function<size_t>
		{
			size_t operator()(const size_t& val, const size_t& capcity) const
			{
				
			}
		};


		//哈希值比较
		//*************************************************************************
		template<class T> struct __hash_equal
		{
			bool operator()(const T& hash1, const T& hash2)
			{
				return hash1 == hash2;
			}
		};
	}
}



#endif // !GHASH_FUNCTION_H
