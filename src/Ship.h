#pragma once
#include "DynBody.h"
#include "Particle.h"
#include "Explosion.h"

class Ship : public DynBody
{
	HTEXTURE hTexture;
	ParticleSys* lpParticle[2];
	Explosion* lpExplosion;

	public:
	float EngineForce;
	Vertex Alignment;

	Ship(HTEXTURE hTexture);
	~Ship();

	void Turn(int dRotate);
	void Thrust(int ForceDirection);
	void Update();
	void Explode();
	void Render();
};
