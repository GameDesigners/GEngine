#ifndef GHASH_FUNCTION_H
#define GHASH_FUNCTION_H

namespace GEngine {
	namespace GStl {
        #define HASH_FUNC_TEMPLATE_TITLE template<>

		template<class T> struct __hash_function {};

		//ƫ�ػ��������Զ������͵Ĺ�ϣֵ�����������
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


		//��ϣֵ�Ƚ�
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
