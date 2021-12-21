#ifndef GMATH_H
#define GMATH_H

#define GMATH_EXPORTS
#ifdef GMATH_EXPORTS
#define GMATH_API __declspec(dllexport) 
#else 
#define GMATH_API __declspec(dllimport) 
#endif


namespace GEngine {
	namespace GMath {


//浮点数类型
#define GFloat     float
#define GDouble   double
#define GLDouble  long double




	}
}

//是否启用加速数学库
#define SSE_ENABLE
#ifdef SSE_ENABLE
#include <mmintrin.h>               //mmx
#include <xmmintrin.h>              //sse
#include <emmintrin.h>              //sse2
#include <pmmintrin.h>              //sse3
#endif // !SSE_ENABLE

#endif // !GMATH_H
