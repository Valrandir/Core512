#include "Core512.h"
#include "Ship.h"
#include "Core/DynBody.h"

HTEXTURE hTex;

DynBody* ThaSmirnoffIceShipOfDoom;

float EngineForce; //Engine Force

void ShipInit()
{
	EngineForce = 50.0f;
	hTex = lpHGE->Texture_Load("Res\\Ship.png");
	ThaSmirnoffIceShipOfDoom = new DynBody(Vertex(0,0), hTex);
}

void ShipUnload()
{
	DeleteNull(ThaSmirnoffIceShipOfDoom);
	lpHGE->Texture_Free(hTex);
	hTex = NULL;
}

void ShipDraw()
{
	ThaSmirnoffIceShipOfDoom->Draw();
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
