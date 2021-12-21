#ifndef GVECTORS_H
#define GVECTORS_H
#include "GMath.h"
#include "GFastCaculateFunction.cpp"

namespace GEngine {
	namespace GMath {
		class GMATH_API GVector2
		{
		public:
			union
			{
				GFloat m[2];
				struct
				{
					GFloat x, y;
				};
			};

		public:
			GVector2();
			GVector2(GFloat val);
			GVector2(GFloat _x, GFloat _y);
			~GVector2();

			static GFloat Angle(const GVector2& from, const GVector2& to);
			static GFloat Dot(const GVector2& from, const GVector2& to);
			static GFloat Distance(GVector2& point1, const GVector2& point2);
			static GVector2 Lerp(GVector2& from, GVector2& to, GFloat weight);
			static GVector2 LerpUnclamped(GVector2& from, GVector2& to, GFloat weight);
			static GVector2 Min(const GVector2& vec1, const GVector2& vec);
			static GVector2 Max(const GVector2& vec1, const GVector2& vec);
			static GVector2 MoveTowards(GVector2 current, GVector2 target, GFloat maxMoveDelta);
			static GVector2 Reflection(GVector2 direction, GVector2 normal);

			inline GFloat Magnitude() const;
			inline GVector2 Normalized() const;
			inline GFloat SqrtMagnitude() const;

			/*²Ù×÷ºÍÔËËã*/
			bool Equal(const GVector2& vec) const;
			void Normalize();
			void Set(GFloat _x, GFloat _y);

			GFloat& operator[](int idx);
			GVector2 operator*(const GVector2& vec);
			void operator+=(const GVector2& vec);
			void operator-=(const GVector2& vec);
			GVector2 operator+(const GVector2& vec);
			GVector2 operator-(const GVector2& vec);
			void operator+=(float const_val);
			void operator-=(GFloat const_val);
			void operator*=(GFloat const_val);
			void operator/=(GFloat const_val);
			GVector2 operator+(GFloat const_val);
			GVector2 operator-(GFloat const_val);
			GVector2 operator*(GFloat const_val);
			GVector2 operator/(GFloat const_val);
		};
	}
}

#endif // !GVECTORS_H
