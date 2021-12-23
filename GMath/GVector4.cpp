#include "GVector4.h"
using namespace GEngine::GMath;

GEngine::GMath::GVector4::GVector4()
{
	Set(0, 0, 0, 0);
}

GEngine::GMath::GVector4::GVector4(GFloat val)
{
	Set(val, val, val, val);
}

GEngine::GMath::GVector4::GVector4(GFloat _x, GFloat _y, GFloat _z, GFloat _w)
{
	Set(_x, _y, _z, _w);
}

GEngine::GMath::GVector4::~GVector4() {}

GFloat GEngine::GMath::GVector4::Distance(const GVector4& point1, const GVector4& point2)
{
	return (point1 - point2).Magnitude();
}

GFloat GEngine::GMath::GVector4::Dot(const GVector4& lhs, const GVector4& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

GVector4 GEngine::GMath::GVector4::Lerp(const GVector4& from, GVector4& to, GFloat weight)
{
	weight = GClamp01(weight);
	return from * weight + to * (1 - weight);
}

GVector4 GEngine::GMath::GVector4::LerpUnclamped(const GVector4& from, GVector4& to, GFloat weight)
{
	return from * weight + to * (1 - weight);
}

GVector4 GEngine::GMath::GVector4::Max(const GVector4& lhs, const GVector4& rhs)
{
	GFloat min_x = lhs.x > rhs.x ? lhs.x : rhs.x;
	GFloat min_y = lhs.y > rhs.y ? lhs.y : rhs.y;
	GFloat min_z = lhs.z > rhs.z ? lhs.z : rhs.z;
	GFloat min_w = lhs.w > rhs.w ? lhs.w : rhs.w;
	return GVector4(min_x, min_y, min_z, min_w);
}

GVector4 GEngine::GMath::GVector4::Min(const GVector4& lhs, const GVector4& rhs)
{
	GFloat min_x = lhs.x < rhs.x ? lhs.x : rhs.x;
	GFloat min_y = lhs.y < rhs.y ? lhs.y : rhs.y;
	GFloat min_z = lhs.z < rhs.z ? lhs.z : rhs.z;
	GFloat min_w = lhs.w < rhs.w ? lhs.w : rhs.w;
	return GVector4(min_x, min_y, min_z, min_w);
}

GVector4 GEngine::GMath::GVector4::MoveTowards(const GVector4& current, const GVector4& target, float maxDistanceDelta)
{
	GVector4 direction = target - current;
	direction.Normalize();
	return direction * maxDistanceDelta;
}

GVector4 GEngine::GMath::GVector4::Scale(const GVector4& lhs, const GVector4& rhs)
{
	return GVector4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
}

inline GFloat GEngine::GMath::GVector4::Magnitude() const
{
	return GSqrt(GPow(x, 2) + GPow(y, 2) + GPow(z, 2) + GPow(w, 2));
}

inline GVector4 GEngine::GMath::GVector4::Normalized() const
{
#ifdef SSE_ENABLE
	GFloat length = GSqrt(GPow(x, 2) + GPow(y, 2) + GPow(z, 2));
	return GVector4(x / length, y / length, z / length, w / length);
#else
	GFloat length = GSqrt(GPow(x, 2) + GPow(y, 2) + GPow(z, 2));
	return GVector4(x / length, y / length, z / length, w / length);
#endif
}

inline GFloat GEngine::GMath::GVector4::SqrtMagnitude() const
{
	return GPow(x, 2) + GPow(y, 2) + GPow(z, 2) + GPow(w, 2);
}

inline bool GEngine::GMath::GVector4::Equal(const GVector4& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
}

inline void GEngine::GMath::GVector4::Normalize()
{
#ifdef SSE_ENABLE
#else
	GFloat length = GSqrt(GPow(x, 2) + GPow(y, 2) + GPow(z, 2));
	m[0] = x = x / length;
	m[1] = y = y / length;
	m[2] = z = z / length;
	m[3] = w = w / length;
#endif
}

inline GEngine::GStl::GTString GEngine::GMath::GVector4::ToString()
{
	GStl::GTString str(L"(");
	str += GStl::to_tstring(x);
	str += L",";
	str += GStl::to_tstring(y);
	str += L",";
	str += GStl::to_tstring(z);
	str += L",";
	str += GStl::to_tstring(w);
	str += L")";
	return str;
}

void GEngine::GMath::GVector4::Set(GFloat _x, GFloat _y, GFloat _z, GFloat _w)
{
	m[0] = x = _x;
	m[1] = y = _y;
	m[2] = z = _z;
	m[3] = w = _w;
}

GVector4 GEngine::GMath::GVector4::operator*(const GVector4& vec) const
{
	return GVector4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}

void GEngine::GMath::GVector4::operator+=(const GVector4& vec)
{
	m[0] = x = x += vec.x;
	m[1] = y = y += vec.y;
	m[2] = z = z += vec.z;
	m[3] = w = w += vec.w;
}

void GEngine::GMath::GVector4::operator-=(const GVector4& vec)
{
	m[0] = x = x -= vec.x;
	m[1] = y = y -= vec.y;
	m[2] = z = z -= vec.z;
	m[3] = w = w -= vec.w;
}

GVector4 GEngine::GMath::GVector4::operator+(const GVector4& vec) const
{
	return GVector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

GVector4 GEngine::GMath::GVector4::operator-(const GVector4& vec) const
{
	return GVector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

void GEngine::GMath::GVector4::operator+=(GFloat fval)
{
	m[0] = x = x += fval;
	m[1] = y = y += fval;
	m[2] = z = z += fval;
	m[3] = w = w += fval;
}

void GEngine::GMath::GVector4::operator-=(GFloat fval)
{
	m[0] = x = x -= fval;
	m[1] = y = y -= fval;
	m[2] = z = z -= fval;
	m[3] = w = w -= fval;
}

void GEngine::GMath::GVector4::operator*=(GFloat fval)
{
	m[0] = x = x *= fval;
	m[1] = y = y *= fval;
	m[2] = z = z *= fval;
	m[3] = w = w *= fval;
}

void GEngine::GMath::GVector4::operator/=(GFloat fval)
{
	GASSERT(fval != 0);
	m[0] = x = x /= fval;
	m[1] = y = y /= fval;
	m[2] = z = z /= fval;
	m[3] = w = w /= fval;
}

GVector4 GEngine::GMath::GVector4::operator+(GFloat fval) const
{
	return GVector4(x + fval, y + fval, z + fval, w + fval);
}

GVector4 GEngine::GMath::GVector4::operator-(GFloat fval) const
{
	return GVector4(x - fval, y - fval, z - fval, w - fval);
}

GVector4 GEngine::GMath::GVector4::operator*(GFloat fval) const
{
	return GVector4(x * fval, y * fval, z * fval, w * fval);
}

GVector4 GEngine::GMath::GVector4::operator/(GFloat fval) const
{
	GASSERT(fval != 0);
	return GVector4(x / fval, y / fval, z / fval, w / fval);
}
