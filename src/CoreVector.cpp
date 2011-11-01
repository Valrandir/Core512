#include "CoreVector.h"

#define Abs(val)((val) > 0 ? (val) : -(val))

CoreVector::CoreVector() : x(Vec.x), y(Vec.y)
{
}

CoreVector::CoreVector(const CoreVector& v) : x(Vec.x), y(Vec.y), Vec(v.x, v.y)
{
}

CoreVector::CoreVector(float x, float y) : x(Vec.x), y(Vec.y), Vec(x, y)
{
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

void CoreVector::Rotate(float Radian)
{
	Vec.Rotate(Radian);
}

void CoreVector::StabilizeEpsilon()
{
	const float Epsilon = 0.01f;

	if(Vec.x && Abs(Vec.x) < Epsilon)
		Vec.x = 0.0f;

	if(Vec.y && Abs(Vec.y) < Epsilon)
		Vec.y = 0.0f;
}
