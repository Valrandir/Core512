#pragma once
#include "CoreVecInt.h"
#include "CoreSprite.h"

class CoreZoneEntity
{
	protected:
	CoreSprite *Sprite;
	CoreVecInt ZoneMapPos; //TopLeft position where this Entity start in CoreZone CoreMap
	CoreVecInt SquareSize; //Pixel size of one square
	CoreVecInt SquareCount; //Number of squares
	
	public:
	CoreZoneEntity(CoreVecInt const & ZoneMapPos, CoreVecInt const & SquareSize);
	virtual ~CoreZoneEntity();
	virtual void Render(const CoreVecInt& ZoneGridPos, const CoreVecInt& Offset) const;

	private:
	void RenderEntityGrid(const CoreVector& Position) const;
};
