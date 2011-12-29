#include "CoreDefs.h"
#include "ShipParticle.h"

ShipParticle::ShipParticle()
{
	CoreTexture* Texture;
	hgeParticleSystemInfo psi = {0};

	ShipParticleEnabled = CoreSys.Config->ShipParticle;
	if(!ShipParticleEnabled) return;

	Texture = CoreSys.Vault->LinkTexture("Res/Particle.png");
	Sprite = CoreSys.CreateCoreSprite(*Texture);

	psi.sprite = Sprite->Sprite;
	psi.nEmission = 200;
	psi.fLifetime = -1.0f;
	psi.fParticleLifeMin = 1.5f;
	psi.fParticleLifeMax = 2.5f;
	psi.fDirection = CoreRad4;
	psi.fSpread = CoreRad32;
	psi.bRelative = true;
	psi.fSpeedMin = 250;
	psi.fSpeedMax = 350;
	psi.fGravityMin = 0;
	psi.fGravityMax = 0;
	psi.fRadialAccelMin = 0;
	psi.fRadialAccelMax = 0;
	psi.fSizeStart = 0.25f;
	psi.fSizeEnd = 2.0f;
	psi.fSizeVar = 0.1f;
	psi.fSpinStart = 0.0f;
	psi.fSpinEnd = CoreRad1;
	psi.fSpinVar = 1.0f;
	psi.colColorStart = 0xFF801040;
	psi.colColorEnd = 0x80000000;
	psi.fColorVar = 0.125;
	psi.fAlphaVar = 0.125;

	lpSys = new hgeParticleSystem(&psi);
}

ShipParticle::~ShipParticle()
{
	if(!ShipParticleEnabled) return;
	lpSys->Stop();
	DeleteNull(lpSys);
	DeleteNull(Sprite);
}

void ShipParticle::Update(const CoreVector& Position, float DirectionRad)
{
	float Delta;

	if(!ShipParticleEnabled) return;

	Delta = CoreSys.Delta();
	lpSys->info.fDirection = DirectionRad;
	lpSys->FireAt(Position.x, Position.y);

	lpSys->Update(Delta);
}

void ShipParticle::Render() const
{
	if(!ShipParticleEnabled) return;
	lpSys->Render();
}

void ShipParticle::Render(const CoreVector& Offset) const
{
	if(!ShipParticleEnabled) return;
	lpSys->Transpose(Offset.x, Offset.y);
	lpSys->Render();
}
