#ifndef GVECTOR2_H
#define GVECTOR2_H
#include "GMath.h"
#include "GFastCaculateFunction.cpp"

namespace GEngine {
	namespace GMath {

		class GMATH_API GVector2
		{
		public:
			GVector2();
			GVector2(GFloat val);
			GVector2(GFloat _x, GFloat _y);
			~GVector2();

			static GFloat Angle(const GVector2& from, const GVector2& to);
			static GFloat Dot(const GVector2& from, const GVector2& to);
			static GFloat Distance(const GVector2& point1, const GVector2& point2);
			static GVector2 ClampMagnitude(const GVector2& vec, GFloat maxLenth);
			static GVector2 Lerp(const GVector2& from, GVector2& to, GFloat weight);
			static GVector2 LerpUnclamped(const GVector2& from, GVector2& to, GFloat weight);
			static GVector2 Min(const GVector2& vec1, const GVector2& vec2);
			static GVector2 Max(const GVector2& vec1, const GVector2& vec2);
			static GVector2 MoveTowards(GVector2 current, GVector2 target, GFloat maxMoveDelta);
			static GVector2 Perpendicular(const GVector2& direction);  //逆时针寻找垂直于direction的向量
			static GVector2 Reflect(const GVector2& direction, const GVector2& normal);
			static GVector2 Scale(const GVector2& vec1, const GVector2& vec2);

			inline GFloat Magnitude() const;
			inline GVector2 Normalized() const;
			inline GFloat SqrtMagnitude() const;

			/*操作和运算*/
			bool Equal(const GVector2& vec) const;
			void Normalize();
			void Set(GFloat _x, GFloat _y);

			GFloat& operator[](int idx);
			GVector2 operator*(const GVector2& vec) const;
			void operator+=(const GVector2& vec);
			void operator-=(const GVector2& vec);
			GVector2 operator+(const GVector2& vec) const;
			GVector2 operator-(const GVector2& vec) const;
			void operator+=(GFloat fval);
			void operator-=(GFloat fval);
			void operator*=(GFloat fval);
			void operator/=(GFloat fval);
			GVector2 operator+(GFloat fval) const;
			GVector2 operator-(GFloat fval) const;
			GVector2 operator*(GFloat fval) const;
			GVector2 operator/(GFloat fval) const;


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
			static GVector2 Down;
			static GVector2 Left;
			static GVector2 NegativeInfinity;
			static GVector2 One;
			static GVector2 PositiveInfinity;
			static GVector2 Right;
			static GVector2 Up;
			static GVector2 Zero;
		};

		GVector2 GEngine::GMath::GVector2::Down(0, -1);
		GVector2 GEngine::GMath::GVector2::Left(-1, 0);
		GVector2 GEngine::GMath::GVector2::NegativeInfinity(-GFLOAT_NAX, -GFLOAT_NAX);
		GVector2 GEngine::GMath::GVector2::One(1, 1);
		GVector2 GEngine::GMath::GVector2::PositiveInfinity(GFLOAT_NAX, GFLOAT_NAX);
		GVector2 GEngine::GMath::GVector2::Right(1, 0);
		GVector2 GEngine::GMath::GVector2::Up(0, 1);
		GVector2 GEngine::GMath::GVector2::Zero(0, 0);

		class GMATH_API GVector2Int
		{
		public:
			GVector2Int();
			GVector2Int(int val);
			GVector2Int(int _x, int _y);
			~GVector2Int();

			static GVector2Int CeilToInt(const GVector2& vec);
			static GVector2Int FloorToInt(const GVector2& vec);
			static GVector2Int RoundToInt(const GVector2& vec);
			static GFloat Distance(const GVector2Int& point1, const GVector2Int& point2);
			static GVector2Int Min(const GVector2Int& vec1, const GVector2Int& vec2);
			static GVector2Int Max(const GVector2Int& vec1, const GVector2Int& vec2);
			static GVector2Int Scale(const GVector2Int& vec1, const GVector2Int& vec2);

			inline GFloat Magnitude() const;
			inline GFloat SqrtMagnitude() const;
			GVector2 ConvertToGVector2();
			bool Equal(const GVector2& vec) const;
			void Set(int _x, int _y);

			int& operator[](int idx);
			GVector2Int operator*(const GVector2Int& vec) const;
			void operator+=(const GVector2Int& vec);
			void operator-=(const GVector2Int& vec);
			GVector2Int operator+(const GVector2Int& vec) const;
			GVector2Int operator-(const GVector2Int& vec) const;
			void operator+=(GFloat fval);
			void operator-=(GFloat fval);
			void operator*=(GFloat fval);
			void operator/=(GFloat fval);
			GVector2Int operator+(GFloat fval) const;
			GVector2Int operator-(GFloat fval) const;
			GVector2Int operator*(GFloat fval) const;
			GVector2Int operator/(GFloat fval) const;


		public:
			union
			{
				int m[2];
				struct
				{
					int x, y;
				};
			};

		public:
			static GVector2Int Down;
			static GVector2Int Left;
			static GVector2Int One;
			static GVector2Int Right;
			static GVector2Int Up;
			static GVector2Int Zero;
		};

		GVector2Int GEngine::GMath::GVector2Int::Down(0, -1);
		GVector2Int GEngine::GMath::GVector2Int::Left(-1, 0);
		GVector2Int GEngine::GMath::GVector2Int::One(1, 1);
		GVector2Int GEngine::GMath::GVector2Int::Right(1, 0);
		GVector2Int GEngine::GMath::GVector2Int::Up(0, 1);
		GVector2Int GEngine::GMath::GVector2Int::Zero(0, 0);
	}
}

#endif // !GVECTORS_H
