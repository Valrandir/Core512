#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <hge.h>
#include "Tools.h"
#include "Ship.h"
#include "Input.h"

HGE* lpHGE;

void CoreLoad();
void CoreUnload();
bool CoreTick();
bool CoreDraw();

int Window_Width = 800;
int Window_Height = 600;

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
	//lpHGE->System_SetState(HGE_FPS, 60);
	lpHGE->System_SetState(HGE_FPS, HGEFPS_VSYNC);
	//lpHGE->System_SetState(HGE_FPS, HGEFPS_UNLIMITED);
	
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
}

void CoreUnload()
{
	ShipUnload();
}

bool CoreTick()
{
	if(lpHGE->Input_GetKeyState(HGEK_ESCAPE))
		return true;

	//Sleep(10);

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
  lpHGE->Gfx_Clear(0);
	float x, y;
	ShipGetCenterPos(x, y);
	rot += 0.1f;
	if(rot > 6.2831853072) rot = 0;
	lpHGE->Gfx_SetTransform(x, y, 0.0f, 0.0f, rot, 1.0f, 1.0f);
  ShipDraw();
  lpHGE->Gfx_EndScene();
	return false;
}
