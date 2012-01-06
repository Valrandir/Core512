#pragma once
#include "CoreZoneEntity.h"
#include "CoreSprite.h"

class Asteroid : public CoreZoneEntity
{
	CoreSprite *Sprite;
	CoreVector ZoneGridPos;

	public:
	Asteroid(CoreVector const & ZoneGridTopLeft);
	~Asteroid();
	void Render() const;
	void Render(const CoreVector& ZoneGridPos, const CoreVector& Offset) const;
};
