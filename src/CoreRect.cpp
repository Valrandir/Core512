#include "CoreRect.h"

CoreRect::CoreRect() {}

void CoreRect::SetByCenter(const CoreVector& Center, const CoreVector& Size)
{
	this->Center = Center;
	this->Size = Size;
	xy1 = Center - Size / 2;
	xy2 = xy1 + Size;
}

void CoreRect::SetByPoints(const CoreVector& xy1, const CoreVector& xy2)
{
	this->xy1 = xy1;
	this->xy2 = xy2;
	Size = xy2 - xy1;
	Center = xy1 + Size / 2;
}

void CoreRect::Move(const CoreVector& Center)
{
	SetByCenter(Center, Size);
}

void CoreRect::Offset(const CoreVector& Vec)
{
	xy1 += Vec;
	xy2 += Vec;
	Center += Vec;
	Size += Vec;
}

//Return true is the specified point is inside this rectangle
bool CoreRect::PointIsInside(const CoreVector& Point) const
{
	return Point.x >= xy1.x && Point.x <= xy2.x && Point.y >= xy1.y && Point.y <= xy2.y;
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
