#include "Core512.h"
#include "Particle.h"

ParticleSys::ParticleSys()
{
	Texture* lpTexture;
	float width, height;
	hgeParticleSystemInfo psi = {0};

	lpTexture = exResources.GetTexture("Res\\Particle.png");
	lpTexture->GetSize(width, height);
	hTexture = lpTexture->hTexture;
	lpSprite = new hgeSprite(hTexture, 0, 0, width, height);
	lpSprite->SetHotSpot(width / 2, height / 2);

	psi.sprite = lpSprite;
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
	psi.colColorStart = 0xA0FF4000;
	psi.colColorEnd = 0x25000000;
	psi.fColorVar = 0.125;
	psi.fAlphaVar = 0.125;

	lpSys = new hgeParticleSystem(&psi);
}

ParticleSys::~ParticleSys()
{
	lpSys->Stop();
	DeleteNull(lpSys);
	DeleteNull(lpSprite);
}

void ParticleSys::Update(float x, float y, float DirectionRad)
{
	float Delta = exHGE->Timer_GetDelta();

	lpSys->info.fDirection = DirectionRad;
	lpSys->FireAt(x, y);

	lpSys->Update(Delta);
}

void ParticleSys::Render()
{
	lpSys->Render();
}
