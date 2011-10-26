#pragma once
#include <hgesprite.h>
#include <hgeparticle.h>

class ParticleSys
{
	HTEXTURE hTexture;
	hgeSprite* lpSprite;
	hgeParticleSystem* lpSys;

	public:
	ParticleSys();
	~ParticleSys();
	void Update(float x, float y, float DirectionRad);
	void Render();
};
