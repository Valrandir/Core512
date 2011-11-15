#pragma once
#include <hgeparticle.h>

class CoreVector;
class CoreSprite;

class ShipParticle
{
	CoreSprite* Sprite;
	hgeParticleSystem* lpSys;

	public:
	ShipParticle();
	~ShipParticle();
	void Update(const CoreVector& Position, float DirectionRad);
	void Render() const;
	void Render(const CoreVector& Offset) const;
};
