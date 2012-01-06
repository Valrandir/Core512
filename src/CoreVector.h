#pragma once
#include <hgevector.h>
class CoreVecInt;

class CoreVector
{
	hgeVector Vec;

	public:
	float &x, &y;

	CoreVector();
	CoreVector(const CoreVector& v);
	CoreVector(const CoreVecInt& v);
	CoreVector(float x, float y);

	bool operator==(const CoreVector& v) const;
	bool operator!=(const CoreVector& v) const;

	CoreVector& operator=(const CoreVector& v);
	CoreVector& operator=(float v);
	CoreVector& operator+=(const CoreVector& v);
	CoreVector& operator+=(float v);
	CoreVector& operator-=(const CoreVector& v);
	CoreVector& operator-=(float v);
	CoreVector& operator*=(const CoreVector& v);
	CoreVector& operator*=(float v);
	CoreVector& operator/=(const CoreVector& v);
	CoreVector& operator/=(float v);

	CoreVector const operator+(const CoreVector& v) const;
	CoreVector const operator+(float v) const;
	CoreVector const operator-(const CoreVector& v) const;
	CoreVector const operator-(float v) const;
	CoreVector const operator*(const CoreVector& v) const;
	CoreVector const operator*(float v) const;
	CoreVector const operator/(const CoreVector& v) const;
	CoreVector const operator/(float v) const;

	void Set(const CoreVector& v);
	void Set(float x, float y);
	void Rotate(float Radian);
	void Normalize();
	void StabilizeEpsilon();
};
