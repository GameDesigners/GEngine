#include "GVector2.h"
using namespace GEngine::GMath;

//GVector2
//**********************************************************************************************************************************************

GEngine::GMath::GVector2::GVector2()
{
	Set(0, 0);
}

GEngine::GMath::GVector2::GVector2(GFloat val)
{
	Set(val, val);
}

GEngine::GMath::GVector2::GVector2(GFloat _x, GFloat _y)
{
	Set(_x, _y);
}

GEngine::GMath::GVector2::~GVector2() {}

GFloat GEngine::GMath::GVector2::Angle(const GVector2& from, const GVector2& to)
{
	GFloat dot = GVector2::Dot(from, to);
	GFloat len_cross = from.Magnitude() * to.Magnitude();
	return GACos(dot / len_cross);
}

GFloat GEngine::GMath::GVector2::Dot(const GVector2& from, const GVector2& to)
{
	return from.x * to.x + from.y * to.y;
}

GFloat GEngine::GMath::GVector2::Distance(const GVector2& point1, const GVector2& point2)
{
	return (point1 - point2).Magnitude();
}

GVector2 GEngine::GMath::GVector2::ClampMagnitude(const GVector2& vec, GFloat maxLength)
{
	GFloat magnitude = vec.Magnitude();
	if (magnitude <= maxLength)
		return vec;
	return vec.Normalized() * maxLength;
}

GVector2 GEngine::GMath::GVector2::Lerp(const GVector2& from, GVector2& to, GFloat weight)
{
	weight = GClamp01(weight);
	return from * weight + to * (1 - weight);
}

GVector2 GEngine::GMath::GVector2::LerpUnclamped(const GVector2& from, GVector2& to, GFloat weight)
{
	return from * weight + to * (1 - weight);
}

GVector2 GEngine::GMath::GVector2::Min(const GVector2& vec1, const GVector2& vec2)
{
	GFloat min_x = vec1.x < vec2.x ? vec1.x : vec2.x;
	GFloat min_y = vec1.y < vec2.y ? vec1.y : vec2.y;
	return GVector2(min_x, min_y);
}

GVector2 GEngine::GMath::GVector2::Max(const GVector2& vec1, const GVector2& vec2)
{
	GFloat max_x = vec1.x > vec2.x ? vec1.x : vec2.x;
	GFloat max_y = vec1.y > vec2.y ? vec1.y : vec2.y;
	return GVector2(max_x, max_y);
}

GVector2 GEngine::GMath::GVector2::MoveTowards(GVector2 current, GVector2 target, GFloat maxMoveDelta)
{
	GVector2 direction = target - current;
	direction.Normalize();
	return direction * maxMoveDelta;
}

GVector2 GEngine::GMath::GVector2::Perpendicular(const GVector2& direction)
{
	return GVector2(-direction.y, direction.x);
}

GVector2 GEngine::GMath::GVector2::Reflect(const GVector2& direction, const GVector2& normal)
{
	GFloat dotx2 = GVector2::Dot(direction, normal) * 2;
	GVector2 projNormalx2 = normal * (dotx2 / normal.SqrtMagnitude());
	return projNormalx2 - direction;

}

GVector2 GEngine::GMath::GVector2::Scale(const GVector2& vec1, const GVector2& vec2)
{
	return GVector2(vec1.x * vec2.x, vec1.y * vec2.y);
}

inline GFloat GEngine::GMath::GVector2::Magnitude() const
{
	return GSqrt(GPow(x, 2) + GPow(y, 2));
}

inline GVector2 GEngine::GMath::GVector2::Normalized() const
{
#ifdef SSE_ENABLE
#else
	GFloat length = GSqrt(GPow(x, 2) + GPow(y, 2));
	return GVector2(x / length, y / length);
#endif
}

inline GFloat GEngine::GMath::GVector2::SqrtMagnitude() const
{
	return GPow(x, 2) + GPow(y, 2);
}

bool GEngine::GMath::GVector2::Equal(const GVector2& vec) const
{
	return vec.x == x && vec.y == y;
}

void GEngine::GMath::GVector2::Normalize()
{
#ifdef SSE_ENABLE
#else
	GFloat length = GSqrt(GPow(x, 2) + GPow(y, 2));
	*this /= length;
#endif
}

void GEngine::GMath::GVector2::Set(GFloat _x, GFloat _y)
{
	m[0] = x = _x;
	m[1] = y = _y;
}

inline GEngine::GStl::GTString GEngine::GMath::GVector2::ToString()
{
	GStl::GTString str(L"(");
	str += GStl::to_tstring(x);
	str += L",";
	str += GStl::to_tstring(y);
	str += L")";
	return str;
}

GFloat& GEngine::GMath::GVector2::operator[](int idx)
{
	return m[idx];
}

GVector2 GEngine::GMath::GVector2::operator*(const GVector2& vec) const
{
	return GVector2(x * vec.x, y * vec.y);
}

void GEngine::GMath::GVector2::operator+=(const GVector2& vec)
{
	m[0] = x += vec.x;
	m[1] = y += vec.y;
}

void GEngine::GMath::GVector2::operator-=(const GVector2& vec)
{
	m[0] = x -= vec.x;
	m[1] = y -= vec.y;
}

GVector2 GEngine::GMath::GVector2::operator+(const GVector2& vec) const
{
	return GVector2(x + vec.x, y + vec.y);
}

GVector2 GEngine::GMath::GVector2::operator-(const GVector2& vec) const
{
	return GVector2(x - vec.x, y - vec.y);
}

void GEngine::GMath::GVector2::operator+=(GFloat fval)
{
	m[0] = x = x + fval;
	m[1] = y = y + fval;
}

void GEngine::GMath::GVector2::operator-=(GFloat fval)
{
	m[0] = x = x - fval;
	m[1] = y = y - fval;
}

void GEngine::GMath::GVector2::operator*=(GFloat fval)
{
	m[0] = x = x * fval;
	m[1] = y = y * fval;
}

void GEngine::GMath::GVector2::operator/=(GFloat fval)
{
	GASSERT(fval != 0);
	m[0] = x = x / fval;
	m[1] = y = y / fval;
}

GVector2 GEngine::GMath::GVector2::operator+(GFloat fval) const
{
	return GVector2(x + fval, y + fval);
}

GVector2 GEngine::GMath::GVector2::operator-(GFloat fval) const
{
	return GVector2(x - fval, y - fval);
}

GVector2 GEngine::GMath::GVector2::operator*(GFloat fval) const
{
	return GVector2(x * fval, y * fval);
}

GVector2 GEngine::GMath::GVector2::operator/(GFloat fval) const
{
	GASSERT(fval != 0);
	return GVector2(x / fval, y / fval);
}



//GVector2Int
//**********************************************************************************************************************************************

GEngine::GMath::GVector2Int::GVector2Int()
{
	Set(0, 0);
}

GEngine::GMath::GVector2Int::GVector2Int(int val)
{
	Set(val, val);
}

GEngine::GMath::GVector2Int::GVector2Int(int _x, int _y)
{
	Set(_x, _y);
}

GEngine::GMath::GVector2Int::~GVector2Int() {}

GVector2Int GEngine::GMath::GVector2Int::CeilToInt(const GVector2& vec)
{
	return GVector2Int(GCeil(vec.x), GCeil(vec.y));
}

GVector2Int GEngine::GMath::GVector2Int::FloorToInt(const GVector2& vec)
{
	return GVector2Int(GFloor(vec.x), GFloor(vec.y));
}

GVector2Int GEngine::GMath::GVector2Int::RoundToInt(const GVector2& vec)
{
	return GVector2Int(GRound(vec.x), GRound(vec.y));
}

GFloat GEngine::GMath::GVector2Int::Distance(const GVector2Int& point1, const GVector2Int& point2)
{
	return (point1 - point2).Magnitude();
}

GVector2Int GEngine::GMath::GVector2Int::Min(const GVector2Int& vec1, const GVector2Int& vec2)
{
	int min_x = vec1.x < vec2.x ? vec1.x : vec2.x;
	int min_y = vec1.y < vec2.y ? vec1.y : vec2.y;
	return GVector2Int(min_x, min_y);
}

GVector2Int GEngine::GMath::GVector2Int::Max(const GVector2Int& vec1, const GVector2Int& vec2)
{
	int min_x = vec1.x > vec2.x ? vec1.x : vec2.x;
	int min_y = vec1.y > vec2.y ? vec1.y : vec2.y;
	return GVector2Int(min_x, min_y);
}

GVector2Int GEngine::GMath::GVector2Int::Scale(const GVector2Int& vec1, const GVector2Int& vec2)
{
	return GVector2Int(vec1.x * vec2.x, vec1.y * vec2.y);
}

inline GFloat GEngine::GMath::GVector2Int::Magnitude() const
{
	return GSqrt(GPow(x, 2) + GPow(y, 2));
}

inline GFloat GEngine::GMath::GVector2Int::SqrtMagnitude() const
{
	return GPow(x, 2) + GPow(y, 2);
}

GVector2 GEngine::GMath::GVector2Int::ConvertToGVector2()
{
	return GVector2(x, y);
}

bool GEngine::GMath::GVector2Int::Equal(const GVector2& vec) const
{
	return x == vec.x && y == vec.y;
}

void GEngine::GMath::GVector2Int::Set(int _x, int _y)
{
	m[0] = x = _x;
	m[1] = y = _y;
}

inline GEngine::GStl::GTString GEngine::GMath::GVector2Int::ToString()
{
	GStl::GTString str(L"(");
	str += GStl::to_tstring(x);
	str += L",";
	str += GStl::to_tstring(y);
	str += L")";
	return str;
}

int& GEngine::GMath::GVector2Int::operator[](int idx)
{
	return m[idx];
}

GVector2Int GEngine::GMath::GVector2Int::operator*(const GVector2Int& vec) const
{
	return GVector2Int(x * vec.x, y * vec.y);
}

void GEngine::GMath::GVector2Int::operator+=(const GVector2Int& vec)
{
	m[0] = x += vec.x;
	m[1] = y += vec.y;
}

void GEngine::GMath::GVector2Int::operator-=(const GVector2Int& vec)
{
	m[0] = x -= vec.x;
	m[1] = y -= vec.y;
}

GVector2Int GEngine::GMath::GVector2Int::operator+(const GVector2Int& vec) const
{
	return GVector2Int(x + vec.x, y + vec.y);
}

GVector2Int GEngine::GMath::GVector2Int::operator-(const GVector2Int& vec) const
{
	return GVector2Int(x - vec.x, y - vec.y);
}

void GEngine::GMath::GVector2Int::operator+=(GFloat fval)
{
	m[0] = x = x + fval;
	m[1] = y = y + fval;
}

void GEngine::GMath::GVector2Int::operator-=(GFloat fval)
{
	m[0] = x = x - fval;
	m[1] = y = y - fval;
}

void GEngine::GMath::GVector2Int::operator*=(GFloat fval)
{
	m[0] = x = x * fval;
	m[1] = y = y * fval;
}

void GEngine::GMath::GVector2Int::operator/=(GFloat fval)
{
	GASSERT(fval != 0);
	m[0] = x = x / fval;
	m[1] = y = y / fval;
}

GVector2Int GEngine::GMath::GVector2Int::operator+(GFloat fval) const
{
	return GVector2Int(x + fval, y + fval);
}

GVector2Int GEngine::GMath::GVector2Int::operator-(GFloat fval) const
{
	return GVector2Int(x - fval, y - fval);
}

GVector2Int GEngine::GMath::GVector2Int::operator*(GFloat fval) const
{
	return GVector2Int(x * fval, y * fval);
}

GVector2Int GEngine::GMath::GVector2Int::operator/(GFloat fval) const
{
	GASSERT(fval != 0);
	return GVector2Int(x / fval, y / fval);
}
