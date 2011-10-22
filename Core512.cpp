#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Core512.h"
#include <hge.h>
#include <hgesprite.h>
#include "Input.h"
#include "Core/Ship.h"
#include "Core/Body.h"
#include "Core/DynBody.h"

void CoreLoad();
void CoreUnload();
bool CoreUpdate();
bool CoreRender();

HGE* lpHGE;

//#define small
//#define medium
#define big

#ifdef small
	int Window_Width = 400;
	int Window_Height = 300;
#elif defined medium
	int Window_Width = 1024;
	int Window_Height = 768;
#elif defined big
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
	
	lpHGE->System_SetState(HGE_FRAMEFUNC, CoreUpdate);
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

bool CoreUpdate()
{
	if(lpHGE->Input_GetKeyState(HGEK_ESCAPE))
		return true;

	Vertex Force(1.0f, 0.0f);
	lpDynBody->ApplyForce(Force);
	lpDynBody->RotationOffset(0.1f);
	lpDynBody->Update();

	int Command = InputGetCommand();
	if(Command == CMD_SHIP_RESET)
	{
		float cx = float(Window_Width >> 1);
		float cy = float(Window_Height >> 1);
		lpShip->Move(cx, cy);
		lpShip->HardStop();
	}

	int ForceDirection, RotationDirection;
	InputGetDirection(ForceDirection, RotationDirection);

	lpShip->Turn(RotationDirection);
	lpShip->Thrust(ForceDirection);
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
