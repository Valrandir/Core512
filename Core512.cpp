#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <hge.h>
#include "Tools.h"
#include "Ship.h"
#include "Input.h"
#include "Core\Body.h"
#include "Core\DynBody.h"

#define DeleteNull(ptr)if(ptr){delete (ptr);(ptr)=NULL;}

void CoreLoad();
void CoreUnload();
bool CoreTick();
bool CoreDraw();

HGE* lpHGE;
int Window_Width = 800 / 2;
int Window_Height = 600 / 2;

HTEXTURE hDefaultBodyTexture = NULL;
Body* lpBody = NULL;
DynBody* lpDynBody = NULL;

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
	lpHGE->System_SetState(HGE_RENDERFUNC, CoreDraw);

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
	ShipInit();

	hDefaultBodyTexture = lpHGE->Texture_Load("Res\\Body.png");

	lpBody = new Body(Vertex(200, 200), 16, 16);
	lpBody->SetTexture(hDefaultBodyTexture);

	lpDynBody = new DynBody(Vertex(220, 150), 16, 16);
	lpDynBody->SetTexture(hDefaultBodyTexture);
}

void CoreUnload()
{
	ShipUnload();

	DeleteNull(lpBody)
	DeleteNull(lpDynBody)

	if(hDefaultBodyTexture)
	{
		lpHGE->Texture_Free(hDefaultBodyTexture);
		hDefaultBodyTexture = NULL;
	}
}

bool CoreTick()
{
	if(lpHGE->Input_GetKeyState(HGEK_ESCAPE))
		return true;

	Vertex Force(1.0f, 0.0f);
	lpDynBody->ApplyForce(Force);
	lpDynBody->Update();

	int dx, dy;
	InputGetDirection(dx, dy);

	ShipThrust(dx, dy);
	ShipTick();

	return false;
}

float rot = 0.0f;

bool CoreDraw()
{
	lpHGE->Gfx_BeginScene();
	lpHGE->Gfx_Clear(ARGB(0xFF, 0xFF, 0xFF, 0xFF));

/*
	float x, y;
	ShipGetCenterPos(x, y);
	rot += 0.1f;
	if(rot > 6.2831853072) rot = 0;
	lpHGE->Gfx_SetTransform(x, y, 0.0f, 0.0f, rot, 1.0f, 1.0f);
*/

	lpBody->Draw();
	lpDynBody->Draw();

	ShipDraw();

	lpHGE->Gfx_EndScene();

	return false;
}
