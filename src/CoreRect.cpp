#include "CoreRect.h"

#define Min(a,b)((a) < (b) ? (a) : (b))
#define Max(a,b)((a) > (b) ? (a) : (b))

CoreRect::CoreRect() {}

CoreRect& CoreRect::SetByCenter(const CoreVector& Size)
{
	this->Center = 0;
	this->Size = Size;
	xy1 = Center - Size / 2;
	xy2 = xy1 + Size;
	return *this;
}

CoreRect& CoreRect::SetByCenter(const CoreVector& Center, const CoreVector& Size)
{
	this->Center = Center;
	this->Size = Size;
	xy1 = Center - Size / 2;
	xy2 = xy1 + Size;
	return *this;
}

CoreRect& CoreRect::SetByPoints(const CoreVector& xy1, const CoreVector& xy2)
{
	this->xy1 = xy1;
	this->xy2 = xy2;
	Size = xy2 - xy1;
	Center = xy1 + Size / 2;
	return *this;
}

CoreRect& CoreRect::SetByPoints(float x1, float y1, float x2, float y2)
{
	return SetByPoints(CoreVector(x1, y1), CoreVector(x2, y2));
}

CoreRect& CoreRect::Clone(CoreRect& Specimen) const
{
	Specimen.SetByCenter(Center, Size);
	return Specimen;
}

CoreRect& CoreRect::Move(const CoreVector& Center)
{
	SetByCenter(Center, Size);
	return *this;
}

CoreRect& CoreRect::Offset(const CoreVector& Vec)
{
	xy1 += Vec;
	xy2 += Vec;
	Center += Vec;
	return *this;
}

CoreRect& CoreRect::RoundToPixel()
{
	xy1.x = (float)(int)xy1.x;
	xy1.y = (float)(int)xy1.y;
	xy2.x = (float)(int)xy2.x;
	xy2.y = (float)(int)xy2.y;
	return *this;
}

//Return true is the specified point is inside this rectangle
bool CoreRect::IsInside(const CoreVector& Point) const
{
	return Point.x >= xy1.x && Point.x <= xy2.x && Point.y >= xy1.y && Point.y <= xy2.y;
}

bool CoreRect::Intersect(const CoreRect& Rect) const
{
	auto x = (Center.x < Rect.Center.x ? xy2.x < Rect.xy1.x : Rect.xy2.x < xy1.x);
	auto y = (Center.y < Rect.Center.y ? xy2.y < Rect.xy1.y : Rect.xy2.y < xy1.y);
	return !x & !y;
}

bool CoreRect::Intersect(const CoreRect& Rect, CoreRect& Intersection) const
{
	bool Intersected = Intersect(Rect);

	if(Intersected)
	{
		CoreVector xy1(Max(xy1.x, Rect.xy1.x), Max(xy1.y, Rect.xy1.y));
		CoreVector xy2(Min(xy2.x, Rect.xy2.x), Min(xy2.y, Rect.xy2.y));
		Intersection.SetByPoints(xy1, xy2);
	}
	else
		Intersection.SetByCenter(CoreVector());

	return Intersected;
}

//Get the CoreVector of the xy distance between the specified point
//and the limits (border) of this rectangle
//Return true is the specified point was outside
bool CoreRect::PointOffset(const CoreVector& Point, CoreVector& Offset) const
{
	if(Point.x < xy1.x)
		Offset.x = Point.x - xy1.x;
	else if(Point.x > xy2.x)
		Offset.x = Point.x - xy2.x;
	else
		Offset.x = 0;

	if(Point.y < xy1.y)
		Offset.y = Point.y - xy1.y;
	else if(Point.y > xy2.y)
		Offset.y = Point.y - xy2.y;
	else
		Offset.y = 0;

	return Offset.x || Offset.y;
}
