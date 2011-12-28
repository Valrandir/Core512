#pragma once
#include "CoreVector.h"

class CoreRect
{
	public:
	CoreVector xy1, xy2, Center, Size;

	CoreRect();

	CoreRect& SetByCenter(const CoreVector& Size);
	CoreRect& SetByCenter(const CoreVector& Center, const CoreVector& Size);
	CoreRect& SetByPoints(const CoreVector& xy1, const CoreVector& xy2);
	CoreRect& SetByPoints(float x1, float y1, float x2, float y2);
	CoreRect& Clone(CoreRect& Specimen) const;
	CoreRect& Move(const CoreVector& Center);
	CoreRect& Offset(const CoreVector& Vec);
	CoreRect& RoundToPixel();

	bool IsInside(const CoreVector& Point) const;
	bool Intersect(const CoreRect& Rect) const;
	bool Intersect(const CoreRect& Rect, CoreRect& Intersection) const;
	bool PointOffset(const CoreVector& Point, CoreVector& Offset) const;
};
