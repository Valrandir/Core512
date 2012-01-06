#include "CoreDefs.h"
#include "CoreVector.h"

CoreVector::CoreVector() : x(Vec.x), y(Vec.y) {}
CoreVector::CoreVector(const CoreVector& v) : x(Vec.x), y(Vec.y), Vec(v.x, v.y) {}
CoreVector::CoreVector(const CoreVecInt& v) : x(Vec.x), y(Vec.y), Vec((float)v.x, (float)v.y) {}
CoreVector::CoreVector(float x, float y) : x(Vec.x), y(Vec.y), Vec(x, y) {}

bool CoreVector::operator==(const CoreVector& v) const
{
	return Vec.x == v.Vec.x && Vec.y == v.Vec.y;
}

bool CoreVector::operator!=(const CoreVector& v) const
{
	return Vec.x != v.Vec.x || Vec.y != v.Vec.y;
}

CoreVector& CoreVector::operator=(const CoreVector& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

CoreVector& CoreVector::operator=(float v)
{
	x = y = v;
	return *this;
}

CoreVector& CoreVector::operator+=(const CoreVector& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

CoreVector& CoreVector::operator+=(float v)
{
	x += v;
	y += v;
	return *this;
}

CoreVector& CoreVector::operator-=(const CoreVector& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

CoreVector& CoreVector::operator-=(float v)
{
	x -= v;
	y -= v;
	return *this;
}

CoreVector& CoreVector::operator*=(const CoreVector& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

CoreVector& CoreVector::operator*=(float v)
{
	x *= v;
	y *= v;
	return *this;
}

CoreVector& CoreVector::operator/=(const CoreVector& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

CoreVector& CoreVector::operator/=(float v)
{
	x /= v;
	y /= v;
	return *this;
}

const CoreVector CoreVector::operator+(const CoreVector& v) const
{
	return CoreVector(*this) += v;
}

const CoreVector CoreVector::operator+(float v) const
{
	return CoreVector(*this) += v;
}

const CoreVector CoreVector::operator-(const CoreVector& v) const
{
	return CoreVector(*this) -= v;
}

const CoreVector CoreVector::operator-(float v) const
{
	return CoreVector(*this) -= v;
}

const CoreVector CoreVector::operator*(const CoreVector& v) const
{
	return CoreVector(*this) *= v;
}

const CoreVector CoreVector::operator*(float v) const
{
	return CoreVector(*this) *= v;
}

const CoreVector CoreVector::operator/(const CoreVector& v) const
{
	return CoreVector(*this) /= v;
}

const CoreVector CoreVector::operator/(float v) const
{
	return CoreVector(*this) /= v;
}

void CoreVector::Set(const CoreVector& v)
{
	Vec.x = v.x;
	Vec.y = v.y;
}

void CoreVector::Set(float x, float y)
{
	Vec.x = x;
	Vec.y = y;
}

void CoreVector::Rotate(float Radian)
{
	Vec.Rotate(Radian);
}

void CoreVector::Normalize()
{
	Vec.Normalize();
}

void CoreVector::StabilizeEpsilon()
{
	EpsilonStab(Vec.x);
	EpsilonStab(Vec.y);
}
