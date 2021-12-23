#include "GMatrix2X2.h"
using namespace GEngine::GMath;

GEngine::GMath::GMatrix2X2::GMatrix2X2()
{
	Set(0, 0, 0, 0);
}

GEngine::GMath::GMatrix2X2::GMatrix2X2(GFloat fval)
{
	Set(fval, fval, fval, fval);
}

GEngine::GMath::GMatrix2X2::GMatrix2X2(GFloat arr[2][2])
{
	Set(arr[0][0], arr[0][1], arr[1][0], arr[1][1]);
}

GEngine::GMath::GMatrix2X2::GMatrix2X2(GFloat _x0, GFloat _y0, GFloat _x1, GFloat _y1)
{
	Set(_x0, _y0, _x1, _y1);
}

GEngine::GMath::GMatrix2X2::~GMatrix2X2() {}

void GEngine::GMath::GMatrix2X2::Transpose()
{
	GFloat temp = y0;
	y0 = x1;
	x1 = temp;
}

void GEngine::GMath::GMatrix2X2::Set(GFloat _x0, GFloat _y0, GFloat _x1, GFloat _y1)
{
	x0 = _x0;
	y0 = _y0;
	x1 = _x1;
	y1 = _y1;
}

GEngine::GStl::GTString GEngine::GMath::GMatrix2X2::ToString()
{
	GStl::GTString split(L",");
	GStl::GTString str(L"[");
	str += GStl::to_tstring(x0);
	str += split;
	str += GStl::to_tstring(y0);
	str += L"]\n[";
	str += GStl::to_tstring(x1);
	str += split;
	str += GStl::to_tstring(y1);
	str += L"]\n";
	return str;
}

GMatrix2X2 GEngine::GMath::GMatrix2X2::operator+(const GMatrix2X2& matrix) const
{
#ifdef SSE_ENABLE
	__m128 v1 = _mm_set_ps(x0, y0, x1, y1);
	__m128 v2 = _mm_set_ps(matrix.x0, matrix.y0, matrix.x1, matrix.y1);
	__m128 r = _mm_add_ps(v1, v2);
	return GMatrix2X2(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);

#else
	return GMatrix2X2(x0 + matrix.x0, y0 + matrix.y0, x1 + matrix.x1, y1 + matrix.y1);
#endif // SSE_ENABLE

	
}

GMatrix2X2 GEngine::GMath::GMatrix2X2::operator-(const GMatrix2X2& matrix) const
{
#ifdef SSE_ENABLE
	__m128 v1 = _mm_set_ps(x0, y0, x1, y1);
	__m128 v2 = _mm_set_ps(matrix.x0, matrix.y0, matrix.x1, matrix.y1);
	__m128 r = _mm_sub_ps(v1, v2);
	return GMatrix2X2(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);
#else
	return GMatrix2X2(x0 - matrix.x0, y0 - matrix.y0, x1 - matrix.x1, y1 - matrix.y1);
#endif // SSE_ENABLE
}

GMatrix2X2 GEngine::GMath::GMatrix2X2::operator*(const GMatrix2X2& matrix) const
{
#ifdef SSE_ENABLE
	__m128 mul1 = _mm_set_ps(x0, x0, x1, x1);
	__m128 mul2 = _mm_set_ps(matrix.x0, matrix.y0, matrix.x0, matrix.y0);

	__m128 mul3 = _mm_set_ps(y0, y0, y1, y1);
	__m128 mul4 = _mm_set_ps(matrix.x1, matrix.y1, matrix.x1, matrix.y1);

	__m128 r = _mm_add_ps(_mm_mul_ps(mul1, mul2), _mm_mul_ps(mul3, mul4));
	return GMatrix2X2(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);
#else
	return GMatrix2X2(
		x0 * matrix.x0 + y0 * matrix.x1,
		x0 * matrix.y0 + y0 * matrix.y1,
		x1 * matrix.x0 + y1 * matrix.x1,
		x1 * matrix.y0 + y1 * matrix.y1
	);
#endif
}

void GEngine::GMath::GMatrix2X2::operator+=(const GMatrix2X2& matrix)
{
#ifdef SSE_ENABLE
	__m128 v1 = _mm_set_ps(x0, y0, x1, y1);
	__m128 v2 = _mm_set_ps(matrix.x0, matrix.y0, matrix.x1, matrix.y1);
	__m128 r = _mm_sub_ps(v1, v2);
	Set(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);
#else
	Set(x0 - matrix.x0, y0 - matrix.y0, x1 - matrix.x1, y1 - matrix.y1);
#endif // SSE_ENABLE
}

void GEngine::GMath::GMatrix2X2::operator-=(const GMatrix2X2& matrix)
{
#ifdef SSE_ENABLE
	__m128 v1 = _mm_set_ps(x0, y0, x1, y1);
	__m128 v2 = _mm_set_ps(matrix.x0, matrix.y0, matrix.x1, matrix.y1);
	__m128 r = _mm_sub_ps(v1, v2);
	Set(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);
#else
	Set(x0 - matrix.x0, y0 - matrix.y0, x1 - matrix.x1, y1 - matrix.y1);
#endif // SSE_ENABLE
}

void GEngine::GMath::GMatrix2X2::operator*=(const GMatrix2X2& matrix)
{
#ifdef SSE_ENABLE
	__m128 mul1 = _mm_set_ps(x0, x0, x1, x1);
	__m128 mul2 = _mm_set_ps(matrix.x0, matrix.y0, matrix.x0, matrix.y0);

	__m128 mul3 = _mm_set_ps(y0, y0, y1, y1);
	__m128 mul4 = _mm_set_ps(matrix.x1, matrix.y1, matrix.x1, matrix.y1);

	__m128 r = _mm_add_ps(_mm_mul_ps(mul1, mul2), _mm_mul_ps(mul3, mul4));
	Set(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);
#else
	Set(
		x0 * matrix.x0 + y0 * matrix.x1,
		x0 * matrix.y0 + y0 * matrix.y1,
		x1 * matrix.x0 + y1 * matrix.x1,
		x1 * matrix.y0 + y1 * matrix.y1
	);
#endif
}

GMatrix2X2 GEngine::GMath::GMatrix2X2::operator+(GFloat fval) const
{
#ifdef SSE_ENABLE
	__m128 v1 = _mm_set_ps(x0, y0, x1, y1);
	__m128 v2 = _mm_set1_ps(fval);
	__m128 r = _mm_add_ps(v1, v2);
	return GMatrix2X2(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);
#else
	return GMatrix2X2(x0 + fval, y0 + fval, x1 + fval, y1 + fval);
#endif // SSE_ENABLE
}

GMatrix2X2 GEngine::GMath::GMatrix2X2::operator-(GFloat fval) const
{
#ifdef SSE_ENABLE
	__m128 v1 = _mm_set_ps(x0, y0, x1, y1);
	__m128 v2 = _mm_set1_ps(fval);
	__m128 r = _mm_sub_ps(v1, v2);
	return GMatrix2X2(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);
#else
	return GMatrix2X2(x0 - fval, y0 - fval, x1 - fval, y1 - fval);
#endif // SSE_ENABLE
}

GMatrix2X2 GEngine::GMath::GMatrix2X2::operator*(GFloat fval) const
{
#ifdef SSE_ENABLE
	__m128 v1 = _mm_set_ps(x0, y0, x1, y1);
	__m128 v2 = _mm_set1_ps(fval);
	__m128 r = _mm_mul_ps(v1, v2);
	return GMatrix2X2(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);
#else
	return GMatrix2X2(x0 * fval, y0 * fval, x1 * fval, y1 * fval);
#endif // SSE_ENABLE
}

void GEngine::GMath::GMatrix2X2::operator+=(GFloat fval)
{
#ifdef SSE_ENABLE
	__m128 v1 = _mm_set_ps(x0, y0, x1, y1);
	__m128 v2 = _mm_set1_ps(fval);
	__m128 r = _mm_add_ps(v1, v2);
	Set(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);
#else
	Set(x0 + fval, y0 + fval, x1 + fval, y1 + fval);
#endif // SSE_ENABLE
}

void GEngine::GMath::GMatrix2X2::operator-=(GFloat fval)
{
#ifdef SSE_ENABLE
	__m128 v1 = _mm_set_ps(x0, y0, x1, y1);
	__m128 v2 = _mm_set1_ps(fval);
	__m128 r = _mm_sub_ps(v1, v2);
	Set(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);
#else
	Set(x0 - fval, y0 - fval, x1 - fval, y1 - fval);
#endif // SSE_ENABLE
}

void GEngine::GMath::GMatrix2X2::operator*=(GFloat fval)
{
#ifdef SSE_ENABLE
	__m128 v1 = _mm_set_ps(x0, y0, x1, y1);
	__m128 v2 = _mm_set1_ps(fval);
	__m128 r = _mm_mul_ps(v1, v2);
	Set(r.m128_f32[3], r.m128_f32[2], r.m128_f32[1], r.m128_f32[0]);
#else
	Set(x0 * fval, y0 * fval, x1 * fval, y1 * fval);
#endif // SSE_ENABLE
}

bool GEngine::GMath::GMatrix2X2::operator==(const GMatrix2X2& matrix)
{
	return x0 == matrix.x0 && 
		   y0 == matrix.y0 && 
		   x1 == matrix.x1 && 
		   y1 == matrix.y1;
}
