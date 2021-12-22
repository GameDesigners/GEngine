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
			inline GFloat Magnitude() const;
			inline GVector4 Normalized() const;
			inline GFloat SqrtMagnitude() const;
			inline bool Equal(const GVector4& vec) const;
			inline void Normalize();
			inline GStl::GTString ToString();
			void Set(GFloat _x, GFloat _y, GFloat _z, GFloat _w);
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
