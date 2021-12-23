#ifndef GMATRIX3X3_H
#define GMATRIX3X3_H
#include "GMath.h"
#include "GVector3.h"
#include "GFastCaculateFunction.h"

namespace GEngine {
	namespace GMath {
		class GMATH_API GMatrix3X3
		{
		public:
			GMatrix3X3();
			GMatrix3X3(GFloat fval);
			GMatrix3X3(GFloat arr[3][3]);
			GMatrix3X3(GFloat _x0, GFloat _y0, GFloat _z0, GFloat _x1, GFloat _y1, GFloat _z1, GFloat _x2, GFloat _y2, GFloat _z2);
			void operator=(const GMatrix3X3& matrix);

			//!!Important Create Matrix3x3 Functions
			
			void CreateFromDirection(GVector3& direction, const GVector3& up = GVector3::Up);
			void CreateRotationX(GFloat rad);
			void CreateRotationY(GFloat rad);
			void CreateRotationZ(GFloat rad);
			
			/*
			 *  pitch:ÉÏÏÂ¸©Ñö×ª½Ç (ÈÆXÖá Ðý×ª) 
			 *  yaw:Ë®Æ½Æ«º½×ª½Ç  (ÈÆYÖáÐý×ª)
			 *  roll:Ðý×ª½Ç(ÈÆZÖá Ðý×ª)
			 */
			void CreateEluer(GFloat pitch, GFloat yaw, GFloat roll);
			void CreateAxisAngle(const GVector3& axis, GFloat rad);
			void GetAxisAngle(const GVector3& vAxis, GFloat degree);
			void CreateRotation(const GVector3& u, const GVector3& v, const GVector3& n);
			void CreateScale(GFloat _x, GFloat _y, GFloat _z);
			void CreateScale(const GVector3& axis, GFloat scale);
			void GetElur(GFloat& outRoll, GFloat& outPitch, GFloat& outYaw);
			void GetAxisAngle(GVector3& outAxis, GFloat& outDegree);

			//GQuaternion GetQuaternion() const;
			void Lerp(const GMatrix3X3& M1, const GMatrix3X3& M2,GFloat weight);
			void Slerp(const GMatrix3X3& M1, const GMatrix3X3& M2, GFloat weight);
			
			void GetRowVector(GVector3 outRow[3]);
			void GetColumnVector(GVector3 outColumn[3]);
			void GetColumnVector(GVector3& outRow);
		public:
			void Set(GFloat _x0, GFloat _y0, GFloat _z0, GFloat _x1, GFloat _y1, GFloat _z1, GFloat _x2, GFloat _y2, GFloat _z2);
			GFloat* operator[](size_t idx) { return M[idx]; }

			GMatrix3X3 operator+(const GMatrix3X3& matrix) const;
			GMatrix3X3 operator-(const GMatrix3X3& matrix) const;
			GMatrix3X3 operator*(const GMatrix3X3& matrix) const;
			void operator+=(const GMatrix3X3& matrix);
			void operator-=(const GMatrix3X3& matrix);
			void operator*=(const GMatrix3X3& matrix);

			GMatrix3X3 operator+(GFloat fval) const;
			GMatrix3X3 operator-(GFloat fval) const;
			GMatrix3X3 operator*(GFloat fval) const;
			void operator+=(GFloat fval);
			void operator-=(GFloat fval);
			void operator*=(GFloat fval);

			bool operator==(const GMatrix3X3& matrix);

		public:
			union
			{
				GFloat M[3][3];
				GFloat m[9];
				struct
				{
					GFloat x0, y0, z0, 
						   x1, y1, z1, 
						   x2, y2, z2;
				};
			};

		public:
			const static GMatrix3X3 Identity;
		};

		//ÌØÊâ¾ØÕó
		//**********************************************************************************************************************************************

		const GMatrix3X3 GEngine::GMath::GMatrix3X3::Identity(
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		);
	}
}
#endif // !GMATRIX3X3_H
