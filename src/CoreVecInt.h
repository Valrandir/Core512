#pragma once
class CoreVector;

class CoreVecInt
{
	public:
	int x, y;

	CoreVecInt();
	CoreVecInt(const CoreVecInt& v);
	CoreVecInt(const CoreVector& v);
	CoreVecInt(int x, int y);

	bool operator==(const CoreVecInt& v) const;
	bool operator!=(const CoreVecInt& v) const;

	CoreVecInt& operator=(const CoreVecInt& v);
	CoreVecInt& operator=(int v);
	CoreVecInt& operator+=(const CoreVecInt& v);
	CoreVecInt& operator+=(int v);
	CoreVecInt& operator-=(const CoreVecInt& v);
	CoreVecInt& operator-=(int v);
	CoreVecInt& operator*=(const CoreVecInt& v);
	CoreVecInt& operator*=(int v);
	CoreVecInt& operator/=(const CoreVecInt& v);
	CoreVecInt& operator/=(int v);

	CoreVecInt const operator+(const CoreVecInt& v) const;
	CoreVecInt const operator+(int v) const;
	CoreVecInt const operator-(const CoreVecInt& v) const;
	CoreVecInt const operator-(int v) const;
	CoreVecInt const operator*(const CoreVecInt& v) const;
	CoreVecInt const operator*(int v) const;
	CoreVecInt const operator/(const CoreVecInt& v) const;
	CoreVecInt const operator/(int v) const;

	void Set(const CoreVecInt& v);
	void Set(int x, int y);
};
