#include "../Core512.h"
#include "Ship.h"

Ship::Ship(HTEXTURE hTexture) : DynBody(Vertex(), hTexture), hTexture(hTexture)
{
	EngineForce = 100.0f;
	//hTex = lpHGE->Texture_Load("Res\\Ship.png");
	Move(Rect.w, Rect.h);
}

void Ship::Align(Vertex Alignment)
{
	this->Alignment = Alignment;
	//Body::RotationSet(Alignment.Angle());
}

void Ship::Turn(int dRotate)
{
	const float RotateSpeed = 0.05f;
	//float Delta = lpHGE->Timer_GetDelta();
	if(dRotate)
	{
		Body::RotationOffset(dRotate * RotateSpeed/* * Delta*/);
		Alignment.x = 0;
		Alignment.y = 1;
		Alignment.Rotate(Body::RotationGradient);
	}
}

//direction cound be -1, 0, or 1
void Ship::Thrust(int dx, int dy)
{
	Vertex Force;
	//Force.x = dx * EngineForce * Alignment.x;
	//Force.y = dy * EngineForce * Alignment.y;
	Force.x = dx * EngineForce;
	Force.y = dy * EngineForce;
	ApplyForce(Force);
}

void Ship::Update()
{
	DynBody::Update();
}

void Ship::Render()
{
	Body::Render();
}
