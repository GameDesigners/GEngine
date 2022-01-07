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
//����
#define GPI        3.14159265358979323846
#define GPI2       1.57079632679489661923
#define Degs_1Rad  57.29578
#define Rads_1Deg  0.017453293

//����������
#define GFloat     float
#define GDouble    double
#define GLDouble   long double

#define GFLOAT_NAX FLT_MAX
#define GFLOAT_MIN FLT_MIN

//C/C++������ѧ����
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
#define GSqrt      sqrt         // param:double,  return:ƽ����
#define GLog       log		    
#define GLog10     log10	    
							    
#define GCeil      ceilf        //ȡ����
#define GFloor     floorf       //ȡ����
#define GRound     roundf       //��������ȡ��
#define GAbs       fabs         //����ֵ
							    
#define GFrexp     frexp        //��׼��������,f=x*2^p  ,��֪f��x,p
#define GIdexp     idexp        //��frexp�෴
							    
#define GModf      modef        //����������������ͨ��ָ�뷵�أ�����С������
#define GFMod      fmod         //�������������������





		//������ת�Ƕ���
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

//�Ƿ����ü�����ѧ��
#define SSE_ENABLE
#ifdef SSE_ENABLE
#include <mmintrin.h>               //mmx
#include <xmmintrin.h>              //sse
#include <emmintrin.h>              //sse2
#include <pmmintrin.h>              //sse3
#endif // !SSE_ENABLE

#endif // !GMATH_H
