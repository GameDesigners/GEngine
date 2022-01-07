#ifndef GMATH_H
#define GMATH_H
#include <cmath>
#include <float.h>

#include <GSystem.h>
#include <GStrings.h>

#define GMATH_EXPORTS
#ifdef GMATH_EXPORTS
#define GMATH_API __declspec(dllexport) 
#else 
#define GMATH_API __declspec(dllimport) 
#endif


namespace GEngine {
	namespace GMath {
//常数
#define GPI        3.14159265358979323846
#define GPI2       1.57079632679489661923
#define Degs_1Rad  57.29578
#define Rads_1Deg  0.017453293

//浮点数类型
#define GFloat     float
#define GDouble    double
#define GLDouble   long double

#define GFLOAT_NAX FLT_MAX
#define GFLOAT_MIN FLT_MIN

//C/C++常用数学函数
#define GSin       sin
#define GSinf      sinf
#define GCos       cos
#define GCosf      cosf
#define GTan       tan
#define GASin      asin
#define GACos      acos
#define GATan      atan
#define GATan2     atan2
#define GSinh      sinh
#define GCosh      cosh
#define GTanh      tanh

#define GPow       pow
#define GExp       exp
#define GSqrt      sqrt         // param:double,  return:平方根
#define GLog       log		    
#define GLog10     log10	    
							    
#define GCeil      ceilf        //取上整
#define GFloor     floorf       //取下整
#define GRound     roundf       //四舍五入取整
#define GAbs       fabs         //绝对值
							    
#define GFrexp     frexp        //标准化浮点数,f=x*2^p  ,已知f求x,p
#define GIdexp     idexp        //与frexp相反
							    
#define GModf      modef        //将参数的整数部分通过指针返回，返回小数部分
#define GFMod      fmod         //返回两参数相除的余数





		//弧度制转角度制
		inline GFloat GRadToDeg(const GFloat& rad)
		{
			return rad * Degs_1Rad;
		}

		inline GFloat GDegToRad(const GFloat& deg)
		{
			return deg * Rads_1Deg;
		}

		inline GFloat GClamp01(GFloat value)
		{
			return value < 0 ? 0 : (value > 1 ? 1 : value);
		}

		inline GFloat GClamp(GFloat value, GFloat min, GFloat max)
		{
			GASSERT(min <= max);
			return value < min ? min : (value > max ? max : value);
		}

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
