#include "../Core512.h"
#include "Ship.h"

Ship::Ship(HTEXTURE hTexture) : DynBody(Vertex(), hTexture), hTexture(hTexture)
{
	EngineForce = 100.0f;
	//hTex = lpHGE->Texture_Load("Res\\Ship.png");
	Move(Rect.w, Rect.h);
}

//direction cound be -1, 0, or 1
void Ship::Thrust(int dx, int dy)
{
	Vertex Force;
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
	RotationOffset(-0.1f);
	Body::Render();
}
