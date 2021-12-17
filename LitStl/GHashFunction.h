#ifndef GHASH_FUNCTION_H
#define GHASH_FUNCTION_H

namespace GEngine {
	namespace GStl {
        #define HASH_FUNC_TEMPLATE_TITLE template<>

		template<class T> struct __conflict_handling_fun {};
		//偏特化（哈希表碰撞检测函数）
		//**********************************************************************************************************************************************

		HASH_FUNC_TEMPLATE_TITLE struct __conflict_handling_fun<size_t>
		{
			//哈希桶处理碰撞的函数
			size_t operator()(const size_t& hash,const size_t& capcity) const
			{
				return hash % capcity;
			}
		};






		template<class T> struct __extract_key_fun {};
		//偏特化（哈希表碰撞检测函数）
		//**********************************************************************************************************************************************

		HASH_FUNC_TEMPLATE_TITLE struct __extract_key_fun<int>
		{
			int operator()(const int& val)
			{
				return val;
			}
		};







		//哈希值比较
		//**********************************************************************************************************************************************
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
