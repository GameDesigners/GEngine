#ifndef GVECTOR3_H
#define GVECTOR3_H
#include "GMath.h"
#include "GFastCaculateFunction.h"

namespace GEngine {
	namespace GMath {

		class GMATH_API GVector3
		{
		public:
			GVector3();
			GVector3(GFloat val);
			GVector3(GFloat _x, GFloat _y, GFloat _z);
			~GVector3();

		public:
			static GFloat Angle(const GVector3& from, const GVector3& to);
			static GVector3 ClampMagnitude(const GVector3& vec, float maxLength);
			static GVector3 Cross(const GVector3& lhs, const GVector3& rhs);
			static GFloat Distance(const GVector3& point1, const GVector3& point2);
			static GFloat Dot(const GVector3& lhs, const GVector3& rhs);
			static GVector3 Lerp(const GVector3& from, GVector3& to, GFloat weight);
			static GVector3 LerpUnclamped(const GVector3& from, GVector3& to, GFloat weight);
			static GVector3 Min(const GVector3& lhs, const GVector3& rhs);
			static GVector3 Max(const GVector3& lhs, const GVector3& rhs);
			static GVector3 MoveTowards(const GVector3& current, const GVector3& target, float maxDistanceDelta);
			static void OrthoNormalize(GVector3& normal, GVector3& tangent);
			static void OrthoNormalize(GVector3& normal, GVector3& tangent, GVector3& binormal);
			static GVector3 Project(const GVector3& vec, const GVector3& onNormal);
			static GVector3 ProjectOnPlane(const GVector3& vec, const GVector3& planeNormal);
			static GVector3 Reflect(const GVector3& direction, const GVector3& normal);
			static GVector3 RotateTowards(const GVector3& currnet, const GVector3& target, float maxRadiansDelta, float maxMagnitudeDelta);
			static GVector3 Scale(const GVector3& a, const GVector3& b);
			static GVector3 Slerp(const GVector3& a, const GVector3& b, float t);
			static GVector3 SlerpUnclamped(const GVector3& a, const GVector3& b, float t);
			static GVector3 SmoothDamp(const GVector3& current, const GVector3& target, GVector3& currentVelocity, float smoothTime, float deltaTime, float maxSpeed = GFLOAT_NAX);
		public:
			inline GFloat Magnitude() const;
			inline GVector3 Normalized() const;
			inline GFloat SqrtMagnitude() const;
			inline bool Equal(const GVector3& vec) const;
			inline void Normalize();
			inline GStl::GTString ToString();

			void Set(GFloat _x, GFloat _y, GFloat _z);
			GFloat& operator[](size_t idx);

			GVector3 operator*(const GVector3& vec) const;
			void operator+=(const GVector3& vec);
			void operator-=(const GVector3& vec);
			GVector3 operator+(const GVector3& vec) const;
			GVector3 operator-(const GVector3& vec) const;
			void operator+=(GFloat fval);
			void operator-=(GFloat fval);
			void operator*=(GFloat fval);
			void operator/=(GFloat fval);
			GVector3 operator+(GFloat fval) const;
			GVector3 operator-(GFloat fval) const;
			GVector3 operator*(GFloat fval) const;
			GVector3 operator/(GFloat fval) const;

		public:
			union
			{
				GFloat m[3];
				struct
				{
					GFloat x, y, z;
				};
			};

		public:
			static GVector3 Back;
			static GVector3 Down;
			static GVector3 Forward;
			static GVector3 Left;
			static GVector3 NegativeInfinity;
			static GVector3 One;
			static GVector3 PositiveInfinity;
			static GVector3 Right;
			static GVector3 Up;
			static GVector3 Zero;
		};

		GVector3 GEngine::GMath::GVector3::Back(0, 0, -1);
		GVector3 GEngine::GMath::GVector3::Down(0, -1, 0);
		GVector3 GEngine::GMath::GVector3::Forward(0, 0, 1);
		GVector3 GEngine::GMath::GVector3::Left(-1, 0, 0);
		GVector3 GEngine::GMath::GVector3::NegativeInfinity(-GFLOAT_NAX, -GFLOAT_NAX, -GFLOAT_NAX);
		GVector3 GEngine::GMath::GVector3::One(1, 1, 1);
		GVector3 GEngine::GMath::GVector3::PositiveInfinity(GFLOAT_NAX, GFLOAT_NAX, GFLOAT_NAX);
		GVector3 GEngine::GMath::GVector3::Right(1, 0, 0);
		GVector3 GEngine::GMath::GVector3::Up(0, 1, 0);
		GVector3 GEngine::GMath::GVector3::Zero(0, 0, 0);
	}
}

#endif // !GVECTOR3