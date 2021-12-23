#ifndef GMATRIX2X2_H
#define GMATRIX2X2_H
#include "GMath.h"
#include "GFastCaculateFunction.h"

namespace GEngine {
	namespace GMath {
		class GMATH_API GMatrix2X2
		{
		public:
			GMatrix2X2();
			GMatrix2X2(GFloat fval);
			GMatrix2X2(GFloat arr[2][2]);
			GMatrix2X2(GFloat _x0, GFloat _y0, GFloat _x1, GFloat _y1);
			~GMatrix2X2();

		public:
			void Transpose();


			void Set(GFloat _x0, GFloat _y0, GFloat _x1, GFloat _y1);
			GStl::GTString ToString();

		public:
			GFloat* operator[](size_t idx) { return M[idx]; }

			GMatrix2X2 operator+(const GMatrix2X2& matrix) const;
			GMatrix2X2 operator-(const GMatrix2X2& matrix) const;
			GMatrix2X2 operator*(const GMatrix2X2& matrix) const;
			void operator+=(const GMatrix2X2& matrix);
			void operator-=(const GMatrix2X2& matrix);
			void operator*=(const GMatrix2X2& matrix);
			
			GMatrix2X2 operator+(GFloat fval) const;
			GMatrix2X2 operator-(GFloat fval) const;
			GMatrix2X2 operator*(GFloat fval) const;
			void operator+=(GFloat fval);
			void operator-=(GFloat fval);
			void operator*=(GFloat fval);

			bool operator==(const GMatrix2X2& matrix);

		public:
			union
			{
				GFloat M[2][2];
				GFloat m[4];
				struct
				{
					GFloat x0, y0, x1, y1;
				};
			};
		};
	}
}
#endif // !GMATRIX2X2_H

