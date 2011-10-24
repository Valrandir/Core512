#include "../Core512.h"
#include "DynBody.h"

float DynBody::GlobalFriction = 0.97f;

DynBody::DynBody(Vertex Center, float Width, float Height) : Body(Center, Width, Height)
{
}

DynBody::DynBody(Vertex Center, HTEXTURE hTexture) : Body(Center, hTexture)
{
}

void DynBody::ApplyForce(Vertex Force)
{
	Velocity.x += Force.x;
	Velocity.y += Force.y;
	Velocity.StabilizeEpsilon();
}

void DynBody::HardStop()
{
	Velocity.x = 0;
	Velocity.y = 0;
}

void DynBody::Update()
{
	float Delta = exHGE->Timer_GetDelta();
	float x = Rect.cx;
	float y = Rect.cy;

	Velocity.x *= GlobalFriction;
	Velocity.y *= GlobalFriction;

	x += Velocity.x * Delta;
	y += Velocity.y * Delta;

	Move(x, y);
}
