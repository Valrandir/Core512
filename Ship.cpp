#include "Core512.h"
#include "Ship.h"
#include "Core/DynBody.h"

HTEXTURE hTex;

DynBody* ThaSmirnoffIceShipOfDoom;

float EngineForce; //Engine Force

void ShipInit()
{
	EngineForce = 100.0f;
	hTex = lpHGE->Texture_Load("Res\\Ship.png");
	ThaSmirnoffIceShipOfDoom = new DynBody(Vertex(100,100), hTex);
}

void ShipUnload()
{
	DeleteNull(ThaSmirnoffIceShipOfDoom);
	lpHGE->Texture_Free(hTex);
	hTex = NULL;
}

float rot = 0.0f;

void ShipRender()
{
	float x, y;
	ShipGetCenterPos(x, y);

	rot += 0.1f;
	if(rot > 6.2831853072)
		rot = 0;

	ThaSmirnoffIceShipOfDoom->Render();
}

//direction must be -1, 0, or 1
void ShipThrust(int dx, int dy)
{
	Vertex Force;
	Force.x = dx * EngineForce;
	Force.y = dy * EngineForce;
	ThaSmirnoffIceShipOfDoom->ApplyForce(Force);
}

void ShipTick()
{
	ThaSmirnoffIceShipOfDoom->Update();
}

void ShipGetCenterPos(float& x, float& y)
{
	x = ThaSmirnoffIceShipOfDoom->Rect.cx;
	y = ThaSmirnoffIceShipOfDoom->Rect.cy;
}
