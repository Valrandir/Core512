#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Core512.h"
#include <hge.h>
#include <hgesprite.h>
#include "Input.h"
#include "Tools.h"
#include "Core/Ship.h"
#include "Core/Body.h"
#include "Core/DynBody.h"

void CoreLoad();
void CoreUnload();
bool CoreTick();
bool CoreRender();

HGE* lpHGE;

//#define small

#ifdef small
	int Window_Width = 800 / 2;
	int Window_Height = 600 / 2;
#else
	int Window_Width = 1920;
	int Window_Height = 1200;
#endif

HTEXTURE hDefaultBodyTexture = NULL;
HTEXTURE hShipTexture = NULL;
Ship* lpShip = NULL;
Body* lpBody = NULL;
DynBody* lpDynBody = NULL;
hgeSprite* lpSprite = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	lpHGE = hgeCreate(HGE_VERSION);

	lpHGE->System_SetState(HGE_TITLE, "Core512");
	lpHGE->System_SetState(HGE_USESOUND, false);
	lpHGE->System_SetState(HGE_SHOWSPLASH, false);
	lpHGE->System_SetState(HGE_HIDEMOUSE, false);
	lpHGE->System_SetState(HGE_LOGFILE, "LogFile.txt");

	lpHGE->System_SetState(HGE_WINDOWED, true);
	lpHGE->System_SetState(HGE_SCREENWIDTH, Window_Width);
	lpHGE->System_SetState(HGE_SCREENHEIGHT, Window_Height);
	lpHGE->System_SetState(HGE_SCREENBPP, 32);
	lpHGE->System_SetState(HGE_FPS, HGEFPS_VSYNC);
	
	lpHGE->System_SetState(HGE_FRAMEFUNC, CoreTick);
	lpHGE->System_SetState(HGE_RENDERFUNC, CoreRender);

	lpHGE->System_Initiate();

	CoreLoad();

	lpHGE->System_Start();

	CoreUnload();

	lpHGE->System_Shutdown();
	lpHGE->Release();

	return 0;
}

void CoreLoad()
{
	hDefaultBodyTexture = lpHGE->Texture_Load("Res\\Body.png");
	hShipTexture = lpHGE->Texture_Load("Res\\Ship.png");

	lpShip = new Ship(hShipTexture);
	lpBody = new Body(Vertex(200, 200), hDefaultBodyTexture);
	lpDynBody = new DynBody(Vertex(220, 150), hDefaultBodyTexture);

	lpSprite = new hgeSprite(hDefaultBodyTexture, 0, 0, 16, 16);
	lpSprite->SetColor(0xFFFF0000);
}

void CoreUnload()
{
	DeleteNull(lpShip)
	DeleteNull(lpBody)
	DeleteNull(lpDynBody)
	DeleteNull(lpSprite)

	DeleteHgeTexture(hDefaultBodyTexture)
	DeleteHgeTexture(hShipTexture)
}

bool CoreTick()
{
	if(lpHGE->Input_GetKeyState(HGEK_ESCAPE))
		return true;

	Vertex Force(1.0f, 0.0f);
	lpDynBody->ApplyForce(Force);
	lpDynBody->RotationOffset(0.1f);
	lpDynBody->Update();

	int dx, dy;
	InputGetDirection(dx, dy);

	lpShip->Thrust(dx, dy);
	lpShip->Update();

	return false;
}

bool CoreRender()
{
	lpHGE->Gfx_BeginScene();
	lpHGE->Gfx_Clear(ARGB(0xFF, 0xFF, 0xFF, 0xFF));

	lpBody->Render();
	lpDynBody->Render();
	lpSprite->Render(10, 0x20);
	lpShip->Render();

	lpHGE->Gfx_EndScene();

	return false;
}
