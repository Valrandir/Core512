#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <hge.h>
#include "Tools.h"
#include "Ship.h"

HGE* lpHGE;

void CoreLoad();
void CoreUnload();
bool CoreTick();
bool CoreDraw();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	lpHGE = hgeCreate(HGE_VERSION);

	lpHGE->System_SetState(HGE_TITLE, "Core512");
	lpHGE->System_SetState(HGE_USESOUND, false);
	lpHGE->System_SetState(HGE_SHOWSPLASH, false);
	lpHGE->System_SetState(HGE_HIDEMOUSE, false);

	lpHGE->System_SetState(HGE_WINDOWED, true);
  lpHGE->System_SetState(HGE_SCREENWIDTH, 800);
  lpHGE->System_SetState(HGE_SCREENHEIGHT, 600);
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
}

void CoreUnload()
{
	ShipUnload();
}

bool CoreTick()
{
	if(lpHGE->Input_GetKeyState(HGEK_ESCAPE))
		return true;

	return false;
}

bool CoreDraw()
{
  lpHGE->Gfx_BeginScene();
  lpHGE->Gfx_Clear(0);
  ShipDraw();
  lpHGE->Gfx_EndScene();
	return false;
}
