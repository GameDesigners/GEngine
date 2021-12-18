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
		//ƫ�ػ�����ϣ���ȡֵ������
		//**********************************************************************************************************************************************

		HASH_FUNC_TEMPLATE_TITLE struct __extract_key_fun<int>
		{
			size_t operator()(const int& val)
			{
				return static_cast<size_t>(val);
			}
		};

		HASH_FUNC_TEMPLATE_TITLE struct __extract_key_fun<unsigned int>
		{
			size_t operator()(const unsigned int& val)
			{
				return static_cast<size_t>(val);
			}
		};

		HASH_FUNC_TEMPLATE_TITLE struct __extract_key_fun<short>
		{
			size_t operator()(const short& val)
			{
				return static_cast<size_t>(val);
			}
		};



		HASH_FUNC_TEMPLATE_TITLE struct __extract_key_fun<float>
		{
			size_t operator()(const float& val)
			{
				int e = 0;
				float tmp = val;
				if (val < 0)
				{
					tmp = -val;
				}
				e = ceil(log(val));
				return size_t((INT32_MAX + 1.0) * tmp * exp(-e));
			}
		};

		//һ���������ɵĹ�ϣKeyչ��ʽ����T����Ϊint,float�����ͣ�
		#define IMPLEMENT_EXTRACT_HASH_KEY_FUNCTOR1(CLASSNAME,T1,P1) \
		template<> struct __extract_key_fun<CLASSNAME>\
        {\
            size_t operator()(const CLASSNAME& val)\
            {\
                return __extract_key_fun<T1>()(val.P1);\
		    }\
		};\

		//�����������ɵĹ�ϣKeyչ��ʽ����T����Ϊint,float�����ͣ�
		#define IMPLEMENT_EXTRACT_HASH_KEY_FUNCTOR2(CLASSNAME,T1,P1,T2,P2) \
		template<> struct __extract_key_fun<CLASSNAME>\
        {\
            size_t operator()(const CLASSNAME& val)\
            {\
                return __extract_key_fun<T1>()(val.P1)+__extract_key_fun<T2>()(val.P2);\
		    }\
		};\


		//�����������ɵĹ�ϣKeyչ��ʽ����T����Ϊint,float�����ͣ�
		#define IMPLEMENT_EXTRACT_HASH_KEY_FUNCTOR2(CLASSNAME,T1,P1,T2,P2,T3,P3) \
		template<> struct __extract_key_fun<CLASSNAME>\
        {\
            size_t operator()(const CLASSNAME& val)\
            {\
                return __extract_key_fun<T1>()(val.P1)+__extract_key_fun<T2>()(val.P2)+__extract_key_fun<T3>()(val.P3);\
		    }\
		};\





		//��ϣֵ�Ƚ�
		//**********************************************************************************************************************************************
		template<class T> struct __hash_equal
		{
			bool operator()(T& hash1, const T& hash2)
			{
				return hash1 == hash2;
			}
		};
	}
}



#endif // !GHASH_FUNCTION_H
