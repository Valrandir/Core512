#pragma once
#include "CoreZoneEntity.h"
#include "CoreSprite.h"

class Asteroid : public CoreZoneEntity
{
	CoreSprite *Sprite;
	CoreVecInt ZoneMapPos; //TopLeft position where this Entity start in CoreZone CoreMap
	CoreVecInt SquareSize; //Pixel size of one square
	CoreVecInt SquareCount; //Number of squares

	public:
	Asteroid(CoreVecInt const & ZoneMapPos, CoreVecInt const & SquareSize);
	~Asteroid();
	void Render(const CoreVecInt& ZoneGridPos, const CoreVecInt& Offset) const;
};
