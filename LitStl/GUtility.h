#ifndef GUTILITY_H
#define GUTILITY_H

#include "GStlMicro.h"

namespace GEngine{
	namespace GStl {
		template<typename T1, typename T2> struct GPair
		{
			T1 first;
			T2 second;

			GPair();
			GPair(const T1& _first, const T2& _second);
			GPair(T1&& _first, T2&& _second) noexcept;
			GPair(const GPair& rhs);
			GPair(GPair&& rv) noexcept;

			~GPair();

			void swap(GPair<T1, T2>& value);

			GPair& operator=(const GPair& rhs);
			GPair& operator=(GPair&& rv) noexcept;
			bool operator==(const GPair& rhs);
			bool operator!=(const GPair& rhs);
			bool operator<(const GPair& rhs);
			bool operator>(const GPair& rhs);
			bool operator<=(const GPair& rhs);
			bool operator>=(const GPair& rhs);
		};

		template<typename... A>
		class GTuple {};

		template<typename T, typename... Tail>
		class GTuple<T, Tail...> : public GTuple<Tail...>
		{
		public:
			GTuple(const T& _val, Tail... params) : GTuple<Tail...>(params...)
			{
				val = _val;
			}

			~GTuple() {}

			T get_value()
			{
				return val;
			}

		public:
			T val;
		};

		template<>
		class GTuple<> {};

#include "GUtility.inl"

		//GTuple数据类型结构体
		template<int N, typename... Tail>
		struct gtuple_elemenet;

		template<int N>
		struct gtuple_elemenet<N, GTuple<>>
		{
			static_assert(0 > N, "Index outside of GTuple");
		};

		template<int N, typename T, typename... Tail>
		struct gtuple_elemenet<N, GTuple<T, Tail...>> : public gtuple_elemenet< N - 1, GTuple<Tail...>> {};

		template<typename T, typename... Tail>
		struct  gtuple_elemenet<0, GTuple<T, Tail...>>
		{
			using value_type = T;
			using class_type = GTuple<T, Tail...>;
		};







		//模板函数
		//**********************************************************************************************************************************************

		template<typename T1, typename T2> GPair<T1, T2> g_make_pair(T1&& first, T2&& second)
		{
			return GPair<T1, T2>(g_move(first), g_move(second));
		}




		template<int Idx, typename... Tail>
		auto g_get(GTuple<Tail...>& t)
		{
			using _class_type = typename gtuple_elemenet<Idx, GTuple<Tail...>>::class_type;
			return ((_class_type&)t).get_value();
		}

		template<typename T, typename... Tail>
		GTuple<T, Tail...> g_make_tuple(T val, Tail... params)
		{
			return GTuple<T, Tail...>(val, params...);
		}

		template<typename T>
		GTuple<T> g_make_tuple(T val)
		{
			return GTuple<T>(val);
		}
	}
}
#endif // !GUTILITY_H