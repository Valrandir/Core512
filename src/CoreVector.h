#pragma once
#include <hgevector.h>

class CoreVector
{
	hgeVector Vec;

	public:
	float &x, &y;

	CoreVector();
	CoreVector(const CoreVector& v);
	CoreVector(float x, float y);

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

	void Rotate(float Radian);
	void Normalize();
	void StabilizeEpsilon();
};
