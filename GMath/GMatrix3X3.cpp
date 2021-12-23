#include "GMatrix3X3.h"
using namespace GEngine::GMath;

GEngine::GMath::GMatrix3X3::GMatrix3X3()
{
	Set
	(
		0, 0, 0,
		0, 0, 0,
		0, 0, 0
	);
}

GEngine::GMath::GMatrix3X3::GMatrix3X3(GFloat fval)
{
	Set
	(
		fval, fval, fval,
		fval, fval, fval,
		fval, fval, fval
	);
}

GEngine::GMath::GMatrix3X3::GMatrix3X3(GFloat arr[3][3])
{
	Set
	(
		arr[0][0], arr[0][1], arr[0][2],
		arr[1][0], arr[1][1], arr[1][2],
		arr[2][0], arr[2][1], arr[2][2]
	);
}

GEngine::GMath::GMatrix3X3::GMatrix3X3(GFloat _x0, GFloat _y0, GFloat _z0, GFloat _x1, GFloat _y1, GFloat _z1, GFloat _x2, GFloat _y2, GFloat _z2)
{
	x0 = _x0; y0 = _y0;	z0 = _z0;
	x1 = _x1; y1 = _y1;	z1 = _z1;
	x2 = _x2; y2 = _y2;	z2 = _z2;
}

void GEngine::GMath::GMatrix3X3::operator=(const GMatrix3X3& matrix)
{
	Set(
		matrix.x0, matrix.y0, matrix.z0,
		matrix.x1, matrix.y1, matrix.z1,
		matrix.x2, matrix.y2, matrix.z2
	);
}

void GEngine::GMath::GMatrix3X3::CreateFromDirection(GVector3& direction, const GVector3& up)
{
	
}

void GEngine::GMath::GMatrix3X3::CreateRotationX(GFloat rad)
{
	GFloat mCos = GCos(rad);
	GFloat mSin = GSin(rad);

	//ÈÆXÖáµÄÐý×ª¾ØÕó
	Set(
		1, 0,     0,
		0, mCos,  mSin,
		0, -mSin, mCos
	);

}

void GEngine::GMath::GMatrix3X3::CreateRotationY(GFloat rad)
{
	GFloat mCos = GCos(rad);
	GFloat mSin = GSin(rad);

	//ÈÆYÖáµÄÐý×ª¾ØÕó
	Set(
		mCos, 0, -mSin,
		0,    1, 0,
		mSin, 0, mCos
	);
}

void GEngine::GMath::GMatrix3X3::CreateRotationZ(GFloat rad)
{
	GFloat mCos = GCos(rad);
	GFloat mSin = GSin(rad);

	//ÈÆZÖáµÄÐý×ª¾ØÕó
	Set(
		mCos,  mSin, 0,
		-mSin, mCos, 0,
		0,     0,    1
	);
}

void GEngine::GMath::GMatrix3X3::CreateEluer(GFloat pitch, GFloat yaw, GFloat roll)
{
	GFloat Sinx = GSin(pitch);
	GFloat Cosx = GCos(pitch);
	GFloat Siny = GSin(yaw);
	GFloat Cosy = GCos(yaw);
	GFloat Sinz = GSin(roll);
	GFloat Cosz = GCos(roll);

	Set(
		Cosy * Cosz                      , Cosy * Sinz                      , -Siny,
		Sinx * Siny * Cosz - Cosx * Sinz , Sinx * Siny * Sinz + Cosx * Cosz , Sinx * Cosy,
		Cosx * Siny * Cosz + Sinx * Sinz , Cosx * Siny * Sinz - Sinx * Cosz , Cosx * Cosy
	);
}

void GEngine::GMath::GMatrix3X3::CreateAxisAngle(const GVector3& axis, GFloat rad)
{
	GFloat mSin = GSin(rad);
	GFloat mCos = GCos(rad);

	Set(
		mCos + (1 - mCos) * GPow(axis.x, 2)          , (1 - mCos) * axis.x * axis.y - mSin * axis.z , (1 - mCos) * axis.x * axis.z + mSin * axis.y,
		(1 - mCos) * axis.x * axis.y + mSin * axis.z , mCos + (1 - mCos) * GPow(axis.y, 2)          , (1 - mCos) * axis.y * axis.z - mSin * axis.x,
		(1 - mCos) * axis.x * axis.z - mSin * axis.y , (1 - mCos) * axis.y * axis.z + mSin * axis.x , mCos + (1 - mCos) * GPow(axis.z, 2)
	);
}


void GEngine::GMath::GMatrix3X3::Set(GFloat _x0, GFloat _y0, GFloat _z0, GFloat _x1, GFloat _y1, GFloat _z1, GFloat _x2, GFloat _y2, GFloat _z2)
{
	x0 = _x0; y0 = _y0;	z0 = _z0;
	x1 = _x1; y1 = _y1;	z1 = _z1;
	x2 = _x2; y2 = _y2;	z2 = _z2;
}

GMatrix3X3 GEngine::GMath::GMatrix3X3::operator+(const GMatrix3X3& matrix) const
{
#ifdef SSE_ENABLE
	__m128 lhs_v1 = _mm_set_ps(x0, y0, z0, 0);
	__m128 lhs_v2 = _mm_set_ps(x1, y1, z1, 0);
	__m128 lhs_v3 = _mm_set_ps(x2, y2, z2, 0);

	__m128 rhs_v1 = _mm_set_ps(matrix.x0, matrix.y0, matrix.z0, 0);
	__m128 rhs_v2 = _mm_set_ps(matrix.x1, matrix.y1, matrix.z1, 0);
	__m128 rhs_v3 = _mm_set_ps(matrix.x2, matrix.y2, matrix.z2, 0);

	__m128 r1 = _mm_add_ps(lhs_v1, rhs_v1);
	__m128 r2 = _mm_add_ps(lhs_v2, rhs_v2);
	__m128 r3 = _mm_add_ps(lhs_v3, rhs_v3);

	return GMatrix3X3(
		r1.m128_f32[3], r1.m128_f32[2], r1.m128_f32[1],
		r2.m128_f32[3], r2.m128_f32[2], r2.m128_f32[1],
		r3.m128_f32[3], r3.m128_f32[2], r3.m128_f32[1]
	);
#else
	return GMatrix3X3(
		x0 + matrix.x0, y0 + matrix.y0, z0 + matrix.z0,
		x1 + matrix.x1, y1 + matrix.y1, z1 + matrix.z1,
		x2 + matrix.x2, y2 + matrix.y2, z2 + matrix.z2
	);
#endif
}

GMatrix3X3 GEngine::GMath::GMatrix3X3::operator-(const GMatrix3X3& matrix) const
{
#ifdef SSE_ENABLE
	__m128 lhs_v1 = _mm_set_ps(x0, y0, z0, 0);
	__m128 lhs_v2 = _mm_set_ps(x1, y1, z1, 0);
	__m128 lhs_v3 = _mm_set_ps(x2, y2, z2, 0);

	__m128 rhs_v1 = _mm_set_ps(matrix.x0, matrix.y0, matrix.z0, 0);
	__m128 rhs_v2 = _mm_set_ps(matrix.x1, matrix.y1, matrix.z1, 0);
	__m128 rhs_v3 = _mm_set_ps(matrix.x2, matrix.y2, matrix.z2, 0);

	__m128 r1 = _mm_sub_ps(lhs_v1, rhs_v1);
	__m128 r2 = _mm_sub_ps(lhs_v2, rhs_v2);
	__m128 r3 = _mm_sub_ps(lhs_v3, rhs_v3);

	return GMatrix3X3(
		r1.m128_f32[3], r1.m128_f32[2], r1.m128_f32[1],
		r2.m128_f32[3], r2.m128_f32[2], r2.m128_f32[1],
		r3.m128_f32[3], r3.m128_f32[2], r3.m128_f32[1]
	);
#else
	return GMatrix3X3(
		x0 - matrix.x0, y0 - matrix.y0, z0 - matrix.z0,
		x1 - matrix.x1, y1 - matrix.y1, z1 - matrix.z1,
		x2 - matrix.x2, y2 - matrix.y2, z2 - matrix.z2
	);
#endif
}

GMatrix3X3 GEngine::GMath::GMatrix3X3::operator*(const GMatrix3X3& matrix) const
{
	GMatrix3X3 mReturn(0.0f);

#ifdef SSE_ENABLE
	__m128 lhs_v1 = _mm_set_ps(x0, y0, z0, 0);
	__m128 lhs_v2 = _mm_set_ps(x1, y1, z1, 0);
	__m128 lhs_v3 = _mm_set_ps(x2, y2, z2, 0);

	__m128 rhs_v1 = _mm_set_ps(matrix.x0, matrix.x1, matrix.x2, 0);
	__m128 rhs_v2 = _mm_set_ps(matrix.y0, matrix.y1, matrix.y2, 0);
	__m128 rhs_v3 = _mm_set_ps(matrix.z0, matrix.z1, matrix.z2, 0);

	__m128 r = _mm_mul_ps(lhs_v1, rhs_v1);
	mReturn.M[0][0] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v1, rhs_v2);
	mReturn.M[0][1] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v1, rhs_v3);
	mReturn.M[0][0] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];

	r = _mm_mul_ps(lhs_v2, rhs_v1);
	mReturn.M[1][0] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v2, rhs_v2);
	mReturn.M[1][1] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v2, rhs_v3);
	mReturn.M[1][2] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];

	r = _mm_mul_ps(lhs_v3, rhs_v1);
	mReturn.M[2][0] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v3, rhs_v2);
	mReturn.M[2][1] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v3, rhs_v3);
	mReturn.M[2][2] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	
	return mReturn;
#else
	for (unsigned short i = 0; i < 3; i++)
	{
		for (unsigned short j = 0; j < 3; j++)
			for (unsigned short k = 0; k < 3; k++)
				mReturn.M[i][j] += M[i][k] * matrix.M[k][j];
	}
	return mReturn;

#endif
}

void GEngine::GMath::GMatrix3X3::operator+=(const GMatrix3X3& matrix)
{
#ifdef SSE_ENABLE
	__m128 lhs_v1 = _mm_set_ps(x0, y0, z0, 0);
	__m128 lhs_v2 = _mm_set_ps(x1, y1, z1, 0);
	__m128 lhs_v3 = _mm_set_ps(x2, y2, z2, 0);

	__m128 rhs_v1 = _mm_set_ps(matrix.x0, matrix.y0, matrix.z0, 0);
	__m128 rhs_v2 = _mm_set_ps(matrix.x1, matrix.y1, matrix.z1, 0);
	__m128 rhs_v3 = _mm_set_ps(matrix.x2, matrix.y2, matrix.z2, 0);

	__m128 r1 = _mm_add_ps(lhs_v1, rhs_v1);
	__m128 r2 = _mm_add_ps(lhs_v2, rhs_v2);
	__m128 r3 = _mm_add_ps(lhs_v3, rhs_v3);

	Set(
		r1.m128_f32[3], r1.m128_f32[2], r1.m128_f32[1],
		r2.m128_f32[3], r2.m128_f32[2], r2.m128_f32[1],
		r3.m128_f32[3], r3.m128_f32[2], r3.m128_f32[1]
	);
#else
	Set(
		x0 + matrix.x0, y0 + matrix.y0, z0 + matrix.z0,
		x1 + matrix.x1, y1 + matrix.y1, z1 + matrix.z1,
		x2 + matrix.x2, y2 + matrix.y2, z2 + matrix.z2
	);
#endif
}

void GEngine::GMath::GMatrix3X3::operator-=(const GMatrix3X3& matrix)
{
#ifdef SSE_ENABLE
	__m128 lhs_v1 = _mm_set_ps(x0, y0, z0, 0);
	__m128 lhs_v2 = _mm_set_ps(x1, y1, z1, 0);
	__m128 lhs_v3 = _mm_set_ps(x2, y2, z2, 0);

	__m128 rhs_v1 = _mm_set_ps(matrix.x0, matrix.y0, matrix.z0, 0);
	__m128 rhs_v2 = _mm_set_ps(matrix.x1, matrix.y1, matrix.z1, 0);
	__m128 rhs_v3 = _mm_set_ps(matrix.x2, matrix.y2, matrix.z2, 0);

	__m128 r1 = _mm_sub_ps(lhs_v1, rhs_v1);
	__m128 r2 = _mm_sub_ps(lhs_v2, rhs_v2);
	__m128 r3 = _mm_sub_ps(lhs_v3, rhs_v3);

	Set(
		r1.m128_f32[3], r1.m128_f32[2], r1.m128_f32[1],
		r2.m128_f32[3], r2.m128_f32[2], r2.m128_f32[1],
		r3.m128_f32[3], r3.m128_f32[2], r3.m128_f32[1]
	);
#else
	Set(
		x0 - matrix.x0, y0 - matrix.y0, z0 - matrix.z0,
		x1 - matrix.x1, y1 - matrix.y1, z1 - matrix.z1,
		x2 - matrix.x2, y2 - matrix.y2, z2 - matrix.z2
	);
#endif
}

void GEngine::GMath::GMatrix3X3::operator*=(const GMatrix3X3& matrix)
{
#ifdef SSE_ENABLE
	__m128 lhs_v1 = _mm_set_ps(x0, y0, z0, 0);
	__m128 lhs_v2 = _mm_set_ps(x1, y1, z1, 0);
	__m128 lhs_v3 = _mm_set_ps(x2, y2, z2, 0);

	__m128 rhs_v1 = _mm_set_ps(matrix.x0, matrix.x1, matrix.x2, 0);
	__m128 rhs_v2 = _mm_set_ps(matrix.y0, matrix.y1, matrix.y2, 0);
	__m128 rhs_v3 = _mm_set_ps(matrix.z0, matrix.z1, matrix.z2, 0);

	__m128 r = _mm_mul_ps(lhs_v1, rhs_v1);
	M[0][0] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v1, rhs_v2);
    M[0][1] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v1, rhs_v3);
	M[0][0] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];

	r = _mm_mul_ps(lhs_v2, rhs_v1);
	M[1][0] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v2, rhs_v2);
	M[1][1] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v2, rhs_v3);
	M[1][2] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];

	r = _mm_mul_ps(lhs_v3, rhs_v1);
	M[2][0] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v3, rhs_v2);
	M[2][1] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];
	r = _mm_mul_ps(lhs_v3, rhs_v3);
	M[2][2] = r.m128_f32[3] + r.m128_f32[2] + r.m128_f32[1];

#else
	GMatrix3X3 mReturn(0.0f);
	for (unsigned short i = 0; i < 3; i++)
	{
		for (unsigned short j = 0; j < 3; j++)
			for (unsigned short k = 0; k < 3; k++)
				mReturn.M[i][j] += M[i][k] * matrix.M[k][j];
	}
	Set(
		mReturn.x0, mReturn.y0, mReturn.z0,
		mReturn.x1, mReturn.y1, mReturn.z1,
		mReturn.x2, mReturn.y2, mReturn.z2
	);
#endif
}

GMatrix3X3 GEngine::GMath::GMatrix3X3::operator+(GFloat fval) const
{
#ifdef SSE_ENABLE
	__m128 lhs_v1 = _mm_set_ps(x0, y0, z0, 0);
	__m128 lhs_v2 = _mm_set_ps(x1, y1, z1, 0);
	__m128 lhs_v3 = _mm_set_ps(x2, y2, z2, 0);

	__m128 rhs_v1 = _mm_set_ps1(fval);
	__m128 rhs_v2 = _mm_set_ps1(fval);
	__m128 rhs_v3 = _mm_set_ps1(fval);

	__m128 r1 = _mm_add_ps(lhs_v1, rhs_v1);
	__m128 r2 = _mm_add_ps(lhs_v2, rhs_v2);
	__m128 r3 = _mm_add_ps(lhs_v3, rhs_v3);

	return GMatrix3X3(
		r1.m128_f32[3], r1.m128_f32[2], r1.m128_f32[1],
		r2.m128_f32[3], r2.m128_f32[2], r2.m128_f32[1],
		r3.m128_f32[3], r3.m128_f32[2], r3.m128_f32[1]
	);
#else
	return GMatrix3X3(
		x0 + fval, y0 + fval, z0 + fval,
		x1 + fval, y1 + fval, z1 + fval,
		x2 + fval, y2 + fval, z2 + fval
	);
#endif
}

GMatrix3X3 GEngine::GMath::GMatrix3X3::operator-(GFloat fval) const
{
#ifdef SSE_ENABLE
	__m128 lhs_v1 = _mm_set_ps(x0, y0, z0, 0);
	__m128 lhs_v2 = _mm_set_ps(x1, y1, z1, 0);
	__m128 lhs_v3 = _mm_set_ps(x2, y2, z2, 0);

	__m128 rhs_v1 = _mm_set_ps1(fval);
	__m128 rhs_v2 = _mm_set_ps1(fval);
	__m128 rhs_v3 = _mm_set_ps1(fval);

	__m128 r1 = _mm_sub_ps(lhs_v1, rhs_v1);
	__m128 r2 = _mm_sub_ps(lhs_v2, rhs_v2);
	__m128 r3 = _mm_sub_ps(lhs_v3, rhs_v3);

	return GMatrix3X3(
		r1.m128_f32[3], r1.m128_f32[2], r1.m128_f32[1],
		r2.m128_f32[3], r2.m128_f32[2], r2.m128_f32[1],
		r3.m128_f32[3], r3.m128_f32[2], r3.m128_f32[1]
	);
#else
	return GMatrix3X3(
		x0 - fval, y0 - fval, z0 - fval,
		x1 - fval, y1 - fval, z1 - fval,
		x2 - fval, y2 - fval, z2 - fval
	);
#endif
}

GMatrix3X3 GEngine::GMath::GMatrix3X3::operator*(GFloat fval) const
{
#ifdef SSE_ENABLE
	__m128 lhs_v1 = _mm_set_ps(x0, y0, z0, 0);
	__m128 lhs_v2 = _mm_set_ps(x1, y1, z1, 0);
	__m128 lhs_v3 = _mm_set_ps(x2, y2, z2, 0);

	__m128 rhs_v1 = _mm_set_ps1(fval);
	__m128 rhs_v2 = _mm_set_ps1(fval);
	__m128 rhs_v3 = _mm_set_ps1(fval);

	__m128 r1 = _mm_mul_ps(lhs_v1, rhs_v1);
	__m128 r2 = _mm_mul_ps(lhs_v2, rhs_v2);
	__m128 r3 = _mm_mul_ps(lhs_v3, rhs_v3);

	return GMatrix3X3(
		r1.m128_f32[3], r1.m128_f32[2], r1.m128_f32[1],
		r2.m128_f32[3], r2.m128_f32[2], r2.m128_f32[1],
		r3.m128_f32[3], r3.m128_f32[2], r3.m128_f32[1]
	);
#else
	return GMatrix3X3(
		x0 * fval, y0 * fval, z0 * fval,
		x1 * fval, y1 * fval, z1 * fval,
		x2 * fval, y2 * fval, z2 * fval
	);
#endif
}

void GEngine::GMath::GMatrix3X3::operator+=(GFloat fval)
{
	*this = *this + fval;
}

void GEngine::GMath::GMatrix3X3::operator-=(GFloat fval)
{
	*this = *this - fval;
}

void GEngine::GMath::GMatrix3X3::operator*=(GFloat fval)
{
	*this = *this * fval;
}

bool GEngine::GMath::GMatrix3X3::operator==(const GMatrix3X3& matrix)
{
	for (unsigned short idx = 0; idx < 9; idx++) 
	{
		if (m[idx] != matrix.m[idx])
			return false;
	}
	return true;
}
