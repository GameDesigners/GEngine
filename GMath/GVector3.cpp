#include "GVector3.h"
using namespace GEngine::GMath;

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

GVector3Int GEngine::GMath::GVector3Int::Down(0, -1, 0);
GVector3Int GEngine::GMath::GVector3Int::Left(-1, 0, 0);
GVector3Int GEngine::GMath::GVector3Int::One(1, 1, 1);
GVector3Int GEngine::GMath::GVector3Int::Right(1, 0, 0);
GVector3Int GEngine::GMath::GVector3Int::Up(0, 1, 0);
GVector3Int GEngine::GMath::GVector3Int::Zero(0, 0, 0);


//GVector3
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

GVector3 GEngine::GMath::GVector3::Reflect(const GVector3& direction, const GVector3& normal)
{
	GFloat dotx2 = GVector3::Dot(direction, normal) * 2;
	GVector3 projNormalx2 = normal * (dotx2 / normal.SqrtMagnitude());
	return projNormalx2 - direction;
}

inline GFloat GEngine::GMath::GVector3::Magnitude() const
{
	return GSqrt(GPow(x, 2) + GPow(y, 2) + GPow(z, 2));
}

inline GVector3 GEngine::GMath::GVector3::Normalized() const
{
#ifdef SSE_ENABLE
	GFloat length = GSqrt(GPow(x, 2) + GPow(y, 2) + GPow(z, 2));
	return GVector3(x / length, y / length, z / length);
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




//GVector3Int
//**********************************************************************************************************************************************

GEngine::GMath::GVector3Int::GVector3Int()
{
	Set(0, 0, 0);
}

GEngine::GMath::GVector3Int::GVector3Int(int val)
{
	Set(val, val, val);
}

GEngine::GMath::GVector3Int::GVector3Int(int _x, int _y, int _z)
{
	Set(_x, _y, _z);
}

GEngine::GMath::GVector3Int::~GVector3Int() {}

GVector3Int GEngine::GMath::GVector3Int::CeilToInt(const GVector3& vec)
{
	return GVector3Int(GCeil(vec.x), GCeil(vec.y), GCeil(vec.z));
}

GVector3Int GEngine::GMath::GVector3Int::FloorToInt(const GVector3& vec)
{
	return GVector3Int(GFloor(vec.x), GFloor(vec.y), GFloor(vec.z));
}

GVector3Int GEngine::GMath::GVector3Int::RoundToInt(const GVector3& vec)
{
	return GVector3Int(GRound(vec.x), GRound(vec.y), GRound(vec.z));
}

GFloat GEngine::GMath::GVector3Int::Distance(const GVector3Int& point1, const GVector3Int& point2)
{
	return (point1 - point2).Magnitude();
}

GVector3Int GEngine::GMath::GVector3Int::Min(const GVector3Int& lhs, const GVector3Int& rhs)
{
	GFloat min_x = lhs.x < rhs.x ? lhs.x : rhs.x;
	GFloat min_y = lhs.y < rhs.y ? lhs.y : rhs.y;
	GFloat min_z = lhs.z < rhs.z ? lhs.z : rhs.z;
	return GVector3Int(min_x, min_y, min_z);
}

GVector3Int GEngine::GMath::GVector3Int::Max(const GVector3Int& lhs, const GVector3Int& rhs)
{
	GFloat min_x = lhs.x > rhs.x ? lhs.x : rhs.x;
	GFloat min_y = lhs.y > rhs.y ? lhs.y : rhs.y;
	GFloat min_z = lhs.z > rhs.z ? lhs.z : rhs.z;
	return GVector3Int(min_x, min_y, min_z);
}

GVector3Int GEngine::GMath::GVector3Int::Scale(const GVector3Int& lhs, const GVector3Int& rhs)
{
	return GVector3Int(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

inline GFloat GEngine::GMath::GVector3Int::Magnitude() const
{
	return GSqrt(GPow(x, 2) + GPow(y, 2) + GPow(z, 2));
}

inline GFloat GEngine::GMath::GVector3Int::SqrtMagnitude() const
{
	return GPow(x, 2) + GPow(y, 2) + GPow(z, 2);
}

GVector3 GEngine::GMath::GVector3Int::ConvertToGVector3()
{
	return GVector3(x, y, z);
}

bool GEngine::GMath::GVector3Int::Equal(const GVector3Int& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z;
}

void GEngine::GMath::GVector3Int::Set(int _x, int _y, int _z)
{
	m[0] = x = _x;
	m[1] = y = _y;
	m[2] = z = _z;
}

int& GEngine::GMath::GVector3Int::operator[](size_t idx)
{
	return m[idx];
}

GEngine::GStl::GTString GEngine::GMath::GVector3Int::ToString()
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

GVector3Int GEngine::GMath::GVector3Int::operator*(const GVector3Int& vec) const
{
	return GVector3Int(x * vec.x, y * vec.y, z * vec.z);
}

void GEngine::GMath::GVector3Int::operator+=(const GVector3Int& vec)
{
	m[0] = x = x += vec.x;
	m[1] = y = y += vec.y;
	m[2] = z = z += vec.z;
}

void GEngine::GMath::GVector3Int::operator-=(const GVector3Int& vec)
{
	m[0] = x = x -= vec.x;
	m[1] = y = y -= vec.y;
	m[2] = z = z -= vec.z;
}

GVector3Int GEngine::GMath::GVector3Int::operator+(const GVector3Int& vec) const
{
	return GVector3Int(x + vec.x, y + vec.y, z + vec.z);
}

GVector3Int GEngine::GMath::GVector3Int::operator-(const GVector3Int& vec) const
{
	return GVector3Int(x - vec.x, y - vec.y, z - vec.z);
}

void GEngine::GMath::GVector3Int::operator+=(int val)
{
	m[0] = x = x += val;
	m[1] = y = y += val;
	m[2] = z = z += val;
}

void GEngine::GMath::GVector3Int::operator-=(int val)
{
	m[0] = x = x -= val;
	m[1] = y = y -= val;
	m[2] = z = z -= val;
}

void GEngine::GMath::GVector3Int::operator*=(int val)
{
	m[0] = x = x *= val;
	m[1] = y = y *= val;
	m[2] = z = z *= val;
}

void GEngine::GMath::GVector3Int::operator/=(int val)
{
	GASSERT(val != 0);
	m[0] = x = x /= val;
	m[1] = y = y /= val;
	m[2] = z = z /= val;
}

GVector3Int GEngine::GMath::GVector3Int::operator+(int val) const
{
	return GVector3Int(x + val, y + val, z + val);
}

GVector3Int GEngine::GMath::GVector3Int::operator-(int val) const
{
	return GVector3Int(x - val, y - val, z - val);
}

GVector3Int GEngine::GMath::GVector3Int::operator*(int val) const
{
	return GVector3Int(x * val, y * val, z * val);
}

GVector3Int GEngine::GMath::GVector3Int::operator/(int val) const
{
	GASSERT(val != 0);
	return GVector3Int(x / val, y / val, z / val);
}
