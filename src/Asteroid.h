#pragma once
#include "CoreZoneEntity.h"

class Asteroid : public CoreZoneEntity
{
	public:
	Asteroid(CoreVecInt const & ZoneMapPos, CoreVecInt const & SquareSize);
	~Asteroid();
	void Render(const CoreVecInt& ZoneGridPos, const CoreVecInt& Offset) const;
};
