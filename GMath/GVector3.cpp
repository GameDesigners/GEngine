#include "GVector3.h"
using namespace GEngine::GMath;
//GVector2
//**********************************************************************************************************************************************

GEngine::GMath::GVector3::GVector3()
{
	Set(0, 0, 0);
}

GEngine::GMath::GVector3::GVector3(GFloat val)
{
	Set(val, val, val);
}

GEngine::GMath::GVector3::GVector3(GFloat _x, GFloat _y, GFloat _z)
{
	Set(_x, _y, _z);
}

GEngine::GMath::GVector3::~GVector3() {}

GFloat GEngine::GMath::GVector3::Angle(const GVector3& from, const GVector3& to)
{
	GFloat dot = GVector3::Dot(from, to);
	GFloat len_cross = from.Magnitude() * to.Magnitude();
	return GACos(dot / len_cross);
}

GVector3 GEngine::GMath::GVector3::ClampMagnitude(const GVector3& vec, float maxLength)
{
	GFloat magnitude = vec.Magnitude();
	if (magnitude <= maxLength)
		return vec;
	return vec.Normalized() * maxLength;
}

GVector3 GEngine::GMath::GVector3::Cross(const GVector3& lhs, const GVector3& rhs)
{
	//(a2b3-a3b2,a3b1-a1b3,a1b2-a2b1)
	return GVector3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x
	);

}

GFloat GEngine::GMath::GVector3::Distance(const GVector3& point1, const GVector3& point2)
{
	return (point1 - point2).Magnitude();
}

GFloat GEngine::GMath::GVector3::Dot(const GVector3& lhs, const GVector3& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

GVector3 GEngine::GMath::GVector3::Lerp(const GVector3& from, GVector3& to, GFloat weight)
{
	weight = GClamp01(weight);
	return from * weight + to * (1 - weight);
}

GVector3 GEngine::GMath::GVector3::LerpUnclamped(const GVector3& from, GVector3& to, GFloat weight)
{
	return from * weight + to * (1 - weight);
}

GVector3 GEngine::GMath::GVector3::Min(const GVector3& lhs, const GVector3& rhs)
{
	GFloat min_x = lhs.x < rhs.x ? lhs.x : rhs.x;
	GFloat min_y = lhs.y < rhs.y ? lhs.y : rhs.y;
	GFloat min_z = lhs.z < rhs.z ? lhs.z : rhs.z;
	return GVector3(min_x, min_y, min_z);
}

GVector3 GEngine::GMath::GVector3::Max(const GVector3& lhs, const GVector3& rhs)
{
	GFloat min_x = lhs.x > rhs.x ? lhs.x : rhs.x;
	GFloat min_y = lhs.y > rhs.y ? lhs.y : rhs.y;
	GFloat min_z = lhs.z > rhs.z ? lhs.z : rhs.z;
	return GVector3(min_x, min_y, min_z);
}

GVector3 GEngine::GMath::GVector3::MoveTowards(const GVector3& current, const GVector3& target, float maxDistanceDelta)
{
	GVector3 direction = target - current;
	direction.Normalize();
	return direction * maxDistanceDelta;
}

void GEngine::GMath::GVector3::OrthoNormalize(GVector3& normal, GVector3& tangent)
{

}

GVector3 GEngine::GMath::GVector3::Project(const GVector3& vec, const GVector3& onNormal)
{
	GFloat dot = GVector3::Dot(vec, onNormal);
	GFloat sqrtMagnitude = onNormal.SqrtMagnitude();
	return onNormal * dot / sqrtMagnitude;
}

GVector3 GEngine::GMath::GVector3::ProjectOnPlane(const GVector3& vec, const GVector3& planeNormal)
{
	GVector3 projNormal = GVector3::Project(vec, planeNormal);
	return vec - projNormal;
}

inline GFloat GEngine::GMath::GVector3::Magnitude() const
{
	return GSqrt(GPow(x, 2) + GPow(y, 2) + GPow(z, 2));
}

inline GVector3 GEngine::GMath::GVector3::Normalized() const
{
#ifdef SSE_ENABLE
#else
	GFloat length = GSqrt(GPow(x, 2) + GPow(y, 2) + GPow(z, 2));
	return GVector3(x / length, y / length, z / length);
#endif
}

inline GFloat GEngine::GMath::GVector3::SqrtMagnitude() const
{
	return GPow(x, 2) + GPow(y, 2) + GPow(z, 2);
}

inline bool GEngine::GMath::GVector3::Equal(const GVector3& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z;
}

inline void GEngine::GMath::GVector3::Normalize()
{
#ifdef SSE_ENABLE
#else
	GFloat length = GSqrt(GPow(x, 2) + GPow(y, 2) + GPow(z, 2));
	m[0] = x = x / length;
	m[1] = y = y / length;
	m[2] = z = z / length;
#endif
}

inline GEngine::GStl::GTString GEngine::GMath::GVector3::ToString()
{
	GStl::GTString str(L"(");
	str += GStl::to_tstring(x);
	str += L",";
	str += GStl::to_tstring(y);
	str += L",";
	str += GStl::to_tstring(z);
	str += L")";
	return str;
}

void GEngine::GMath::GVector3::Set(GFloat _x, GFloat _y, GFloat _z)
{
	m[0] = x = _x;
	m[1] = y = _y;
	m[2] = z = _z;
}

GFloat& GEngine::GMath::GVector3::operator[](size_t idx)
{
	return m[idx];
}

GVector3 GEngine::GMath::GVector3::operator*(const GVector3& vec) const
{
	return GVector3(x * vec.x, y * vec.y, z * vec.z);
}

void GEngine::GMath::GVector3::operator+=(const GVector3& vec)
{
	m[0] = x = x += vec.x;
	m[1] = y = y += vec.y;
	m[2] = z = z += vec.z;
}

void GEngine::GMath::GVector3::operator-=(const GVector3& vec)
{
	m[0] = x = x -= vec.x;
	m[1] = y = y -= vec.y;
	m[2] = z = z -= vec.z;
}

GVector3 GEngine::GMath::GVector3::operator+(const GVector3& vec) const
{
	return GVector3(x + vec.x, y + vec.y, z + vec.z);
}

GVector3 GEngine::GMath::GVector3::operator-(const GVector3& vec) const
{
	return GVector3(x - vec.x, y - vec.y, z - vec.z);
}

void GEngine::GMath::GVector3::operator+=(GFloat fval)
{
	m[0] = x = x += fval;
	m[1] = y = y += fval;
	m[2] = z = z += fval;
}

void GEngine::GMath::GVector3::operator-=(GFloat fval)
{
	m[0] = x = x -= fval;
	m[1] = y = y -= fval;
	m[2] = z = z -= fval;
}

void GEngine::GMath::GVector3::operator*=(GFloat fval)
{
	m[0] = x = x *= fval;
	m[1] = y = y *= fval;
	m[2] = z = z *= fval;
}

void GEngine::GMath::GVector3::operator/=(GFloat fval)
{
	GASSERT(fval != 0);
	m[0] = x = x /= fval;
	m[1] = y = y /= fval;
	m[2] = z = z /= fval;
}

GVector3 GEngine::GMath::GVector3::operator+(GFloat fval) const
{
	return GVector3(x + fval, y + fval, z + fval);
}

GVector3 GEngine::GMath::GVector3::operator-(GFloat fval) const
{
	return GVector3(x - fval, y - fval, z - fval);
}

GVector3 GEngine::GMath::GVector3::operator*(GFloat fval) const
{
	return GVector3(x * fval, y * fval, z * fval);
}

GVector3 GEngine::GMath::GVector3::operator/(GFloat fval) const
{
	GASSERT(fval != 0);
	return GVector3(x / fval, y / fval, z / fval);
}

