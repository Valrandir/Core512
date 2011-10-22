#include "../Core512.h"
#include "Ship.h"

Ship::Ship(HTEXTURE hTexture) : DynBody(Vertex(), hTexture), hTexture(hTexture)
{
	EngineForce = 100.0f;
	Alignment.x = 0;
	Alignment.y = 1;
	Body::Move(Rect.w, Rect.h);
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
}

void Ship::Render()
{
	Body::Render();
}
