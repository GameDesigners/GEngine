#ifndef GVECTOR4_H
#define GVECTOR4_H
#include "GMath.h"
#include "GFastCaculateFunction.h"

namespace GEngine {
	namespace GMath {
		class GMATH_API GVector4
		{
		public:
			GVector4();
			GVector4(GFloat val);
			GVector4(GFloat _x, GFloat _y, GFloat _z, GFloat _w);
			~GVector4();

		public:
			GFloat Distance(const GVector4& point1, const GVector4& point2);
			GFloat Dot(const GVector4& lhs, const GVector4& rhs);
			static GVector4 Lerp(const GVector4& from, GVector4& to, GFloat weight);
			static GVector4 LerpUnclamped(const GVector4& from, GVector4& to, GFloat weight);
			static GVector4 Max(const GVector4& lhs, const GVector4& rhs);
			static GVector4 Min(const GVector4& lhs, const GVector4& rhs);
			static GVector4 MoveTowards(const GVector4& current, const GVector4& target, float maxDistanceDelta);
			static GVector4 Project(const GVector4& a, const GVector4& b);
			static GVector4 Scale(const GVector4& a, const GVector4& b);

		public:
			inline GFloat Magnitude() const;
			inline GVector4 Normalized() const;
			inline GFloat SqrtMagnitude() const;
			inline bool Equal(const GVector4& vec) const;
			inline void Normalize();
			inline GStl::GTString ToString();
			void Set(GFloat _x, GFloat _y, GFloat _z, GFloat _w);

		public:
			GVector4 operator*(const GVector4& vec) const;
			void operator+=(const GVector4& vec);
			void operator-=(const GVector4& vec);
			GVector4 operator+(const GVector4& vec) const;
			GVector4 operator-(const GVector4& vec) const;
			void operator+=(GFloat fval);
			void operator-=(GFloat fval);
			void operator*=(GFloat fval);
			void operator/=(GFloat fval);
			GVector4 operator+(GFloat fval) const;
			GVector4 operator-(GFloat fval) const;
			GVector4 operator*(GFloat fval) const;
			GVector4 operator/(GFloat fval) const;

		public:
			union
			{
				GFloat m[4];
				struct
				{
					GFloat x, y, z, w;
				};
			};

		public:
			static GVector4 NegativeInfinity;
			static GVector4 One;
			static GVector4 PositiveInfinity;
			static GVector4 Zero;
		};

		GVector4 GEngine::GMath::GVector4::NegativeInfinity(-GFLOAT_NAX, -GFLOAT_NAX, -GFLOAT_NAX, -GFLOAT_NAX);
		GVector4 GEngine::GMath::GVector4::One(1, 1, 1, 1);
		GVector4 GEngine::GMath::GVector4::PositiveInfinity(GFLOAT_NAX, GFLOAT_NAX, GFLOAT_NAX, GFLOAT_NAX);
		GVector4 GEngine::GMath::GVector4::Zero(0, 0, 0, 0);
	}
}
#endif // !GVECTOR4_H
