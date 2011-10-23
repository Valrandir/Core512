#include "../Core512.h"
#include "Ship.h"

Ship::Ship(HTEXTURE hTexture) : DynBody(Vertex(), hTexture), hTexture(hTexture)
{
	EngineForce = 100.0f;
	Alignment.x = 0;
	Alignment.y = 1;
	Body::Move(Rect.w, Rect.h);
	lpParticle[0] = new ParticleSys();
	lpParticle[1] = new ParticleSys();
}

Ship::~Ship()
{
	DeleteNull(lpParticle[0]);
	DeleteNull(lpParticle[1]);
}

void Ship::Turn(int dRotate)
{
	float RotateRad = CoreRad32 * 60;
	float Delta = lpHGE->Timer_GetDelta();

	if(dRotate)
	{
		RotateRad *= dRotate * Delta;
		Alignment.x = 0;
		Alignment.y = 1;

		Body::RotationOffset(RotateRad);
		RotateRad = Body::RotationRadian;

		Alignment.Rotate(RotateRad);
		Alignment.StabilizeEpsilon();
	}
}

//direction cound be -1, 0, or 1
void Ship::Thrust(int ForceDirection)
{
	Vertex Force;

	if(ForceDirection)
	{
		Force.x = ForceDirection * EngineForce * Alignment.x;
		Force.y = ForceDirection * EngineForce * Alignment.y;

		ApplyForce(Force);
	}
}

void Ship::Update()
{
	DynBody::Update();

	Vertex pp[2];
	pp[0].x = Rect.x1 + 16;
	pp[0].y = Rect.y2 - 8;
	pp[1].x = Rect.x2 - 16;
	pp[1].y = Rect.y2 - 8;

	//pp.Normalize();
	//pp.x *= Alignment.x;
	//pp.y *= Alignment.y;

	lpParticle[0]->Update(pp[0].x, pp[0].y, RotationRadian + CoreRad4);
	lpParticle[1]->Update(pp[1].x, pp[1].y, RotationRadian + CoreRad4);
}

void Ship::Render()
{
	Body::Render();
	lpParticle[0]->Render();
	lpParticle[1]->Render();
}
