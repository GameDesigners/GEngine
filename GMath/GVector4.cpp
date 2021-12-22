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

inline GFloat GEngine::GMath::GVector4::Magnitude() const
{
	return GSqrt(GPow(x, 2) + GPow(y, 2) + GPow(z, 2) + GPow(w, 2));
}

inline GVector4 GEngine::GMath::GVector4::Normalized() const
{
#ifdef SSE_ENABLE
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
