#ifndef GSTLMICRO_H
#define GSTLMICRO_H
#include "GSystem.h"


#define GSTL_EXPORTS
#ifdef GSTL_EXPORTS
#define GSTL_API __declspec(dllexport) 
#else 
#define GSTL_API __declspec(dllimport) 
#endif



template<typename T> T&& g_move(T& val)
{
	return static_cast<T&&>(val);
}

template<typename T> void g_swap(T& lhs, T& rhs)
{
	T temp(lhs);
	lhs = g_move(rhs);
	rhs = g_move(temp);
}

#endif // !GSTLMICRO_H
