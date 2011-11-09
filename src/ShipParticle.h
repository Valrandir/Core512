#pragma once
#include <hgesprite.h>
#include <hgeparticle.h>
#include "CoreVector.h"

class ShipParticle
{
	hgeSprite* lpSprite;
	hgeParticleSystem* lpSys;

	public:
	ShipParticle();
	~ShipParticle();
	void Update(const CoreVector& Position, float DirectionRad);
	void Render();
};
