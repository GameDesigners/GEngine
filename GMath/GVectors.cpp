#include "GVectors.h"
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




bool GEngine::GMath::GVector2::Equal(const GVector2& vec) const 
{
	return vec.x == x && vec.y == y;
}

void GEngine::GMath::GVector2::Normalize()
{
}

void GEngine::GMath::GVector2::Set(GFloat _x, GFloat _y)
{
	x = m[0] = _x;
	y = m[1] = _y;
}

GFloat& GEngine::GMath::GVector2::operator[](int idx)
{
	return m[idx];
}

GVector2 GEngine::GMath::GVector2::operator*(const GVector2& vec)
{
	return GVector2(x * vec.x, y * vec.y);
}




