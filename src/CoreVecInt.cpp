#include "CoreVecInt.h"
#include "CoreVector.h"

CoreVecInt::CoreVecInt() : x(0), y(0) {}
CoreVecInt::CoreVecInt(const CoreVecInt& v) : x(v.x), y(v.y) {}
CoreVecInt::CoreVecInt(const CoreVector& v) : x((int)v.x), y((int)v.y) {}
CoreVecInt::CoreVecInt(int x, int y) : x(x), y(y) {}

bool CoreVecInt::operator==(const CoreVecInt& v) const
{
	return x == v.x && y == v.y;
}

bool CoreVecInt::operator!=(const CoreVecInt& v) const
{
	return x != v.x || y != v.y;
}

CoreVecInt& CoreVecInt::operator=(const CoreVecInt& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

CoreVecInt& CoreVecInt::operator=(int v)
{
	x = y = v;
	return *this;
}

CoreVecInt& CoreVecInt::operator+=(const CoreVecInt& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

CoreVecInt& CoreVecInt::operator+=(int v)
{
	x += v;
	y += v;
	return *this;
}

CoreVecInt& CoreVecInt::operator-=(const CoreVecInt& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

CoreVecInt& CoreVecInt::operator-=(int v)
{
	x -= v;
	y -= v;
	return *this;
}

CoreVecInt& CoreVecInt::operator*=(const CoreVecInt& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

CoreVecInt& CoreVecInt::operator*=(int v)
{
	x *= v;
	y *= v;
	return *this;
}

CoreVecInt& CoreVecInt::operator/=(const CoreVecInt& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

CoreVecInt& CoreVecInt::operator/=(int v)
{
	x /= v;
	y /= v;
	return *this;
}

const CoreVecInt CoreVecInt::operator+(const CoreVecInt& v) const
{
	return CoreVecInt(*this) += v;
}

const CoreVecInt CoreVecInt::operator+(int v) const
{
	return CoreVecInt(*this) += v;
}

const CoreVecInt CoreVecInt::operator-(const CoreVecInt& v) const
{
	return CoreVecInt(*this) -= v;
}

const CoreVecInt CoreVecInt::operator-(int v) const
{
	return CoreVecInt(*this) -= v;
}

const CoreVecInt CoreVecInt::operator*(const CoreVecInt& v) const
{
	return CoreVecInt(*this) *= v;
}

const CoreVecInt CoreVecInt::operator*(int v) const
{
	return CoreVecInt(*this) *= v;
}

const CoreVecInt CoreVecInt::operator/(const CoreVecInt& v) const
{
	return CoreVecInt(*this) /= v;
}

const CoreVecInt CoreVecInt::operator/(int v) const
{
	return CoreVecInt(*this) /= v;
}

void CoreVecInt::Set(const CoreVecInt& v)
{
	x = v.x;
	y = v.y;
}

void CoreVecInt::Set(int x, int y)
{
	this->x = x;
	this->y = y;
}
