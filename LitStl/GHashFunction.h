#ifndef GHASH_FUNCTION_H
#define GHASH_FUNCTION_H

namespace GEngine {
	namespace GStl {
        #define HASH_FUNC_TEMPLATE_TITLE template<>

		template<class T> struct __conflict_handling_fun {};
		//ƫ�ػ�����ϣ����ײ��⺯����
		//**********************************************************************************************************************************************

		HASH_FUNC_TEMPLATE_TITLE struct __conflict_handling_fun<size_t>
		{
			//��ϣͰ������ײ�ĺ���
			size_t operator()(const size_t& hash,const size_t& capcity) const
			{
				return hash % capcity;
			}
		};






		template<class T> struct __extract_key_fun {};
		//ƫ�ػ�����ϣ����ײ��⺯����
		//**********************************************************************************************************************************************

		HASH_FUNC_TEMPLATE_TITLE struct __extract_key_fun<int>
		{
			int operator()(const int& val)
			{
				return val;
			}
		};







		//��ϣֵ�Ƚ�
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
