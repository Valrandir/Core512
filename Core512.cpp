#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Core512.h"
#include <hge.h>
#include <hgesprite.h>
#include "Input.h"
#include "Core/Ship.h"
#include "Core/Body.h"
#include "Core/DynBody.h"
#include "TextOut.h"
#include "Music.h"
#include "Background.h"

void CoreLoad();
void CoreInit();
void CoreInput();
void CoreUnload();
bool CoreUpdate();
bool CoreRender();

HGE* lpHGE;
int WindowWidth = 640;
int WindowHeight = 480;

const char* HelpText = "Core512 is best.\n\nControls :\n- Thrust -> Up Arrow / Down Arrow / Mouse Buttons\n- Rotate -> Left Arrow / Right Arrow / D / F\n- Reset Ship -> Space\n- Toggle Background -> T\n- Quit -> Escape";

HTEXTURE hDefaultBodyTexture = NULL;
HTEXTURE hShipTexture = NULL;
Ship* lpShip = NULL;
Body* lpBody = NULL;
DynBody* lpDynBody = NULL;
hgeSprite* lpSprite = NULL;
Font* lpFont = NULL;
Music* lpMusic = NULL;
Background* lpBackground = NULL;

//Size is 75% of screen size
void CalculateAppSize(int& Width, int& Height)
{
	Width = int(GetSystemMetrics(SM_CXSCREEN) * 0.75);
	Height = int(GetSystemMetrics(SM_CYSCREEN) * 0.75);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	CalculateAppSize(WindowWidth, WindowHeight);

	lpHGE = hgeCreate(HGE_VERSION);

	lpHGE->System_SetState(HGE_TITLE, "Core512");
	lpHGE->System_SetState(HGE_USESOUND, true);
	lpHGE->System_SetState(HGE_SHOWSPLASH, false);
	lpHGE->System_SetState(HGE_HIDEMOUSE, false);

	#ifdef _DEBUG
		lpHGE->System_SetState(HGE_LOGFILE, "LogFile.txt");
	#endif

	lpHGE->System_SetState(HGE_WINDOWED, true);
	lpHGE->System_SetState(HGE_SCREENWIDTH, WindowWidth);
	lpHGE->System_SetState(HGE_SCREENHEIGHT, WindowHeight);
	lpHGE->System_SetState(HGE_SCREENBPP, 32);
	lpHGE->System_SetState(HGE_FPS, HGEFPS_VSYNC);

	lpHGE->System_SetState(HGE_FRAMEFUNC, CoreUpdate);
	lpHGE->System_SetState(HGE_RENDERFUNC, CoreRender);

	lpHGE->System_Initiate();

	CoreLoad();
	CoreInit();

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

	lpFont = new Font();
	lpMusic = new Music();
	lpBackground = new Background();
}

void CoreInit()
{
	float cx = float(WindowWidth >> 1);
	float cy = float(WindowHeight >> 1);
	lpShip->Move(cx, cy);

	lpMusic->Play();

	MessageBox(lpHGE->System_GetState(HGE_HWND), HelpText, "Core512", MB_OK | MB_ICONINFORMATION);
}

void CoreUnload()
{
	DeleteNull(lpShip)
	DeleteNull(lpBody)
	DeleteNull(lpDynBody)
	DeleteNull(lpSprite)
	DeleteNull(lpFont)
	DeleteNull(lpMusic)
	DeleteNull(lpBackground);

	DeleteHgeTexture(hDefaultBodyTexture)
	DeleteHgeTexture(hShipTexture)
}

void CoreInput()
{
	int Command = InputGetCommand();

	if(Command == CMD_SHIP_RESET)
	{
		float cx = float(WindowWidth >> 1);
		float cy = float(WindowHeight >> 1);
		lpShip->Move(cx, cy);
		lpShip->HardStop();
	}

	if(Command == CMD_BACKGROUND_TOGGLE)
		lpBackground->Toggle();
}

bool CoreUpdate()
{
	if(lpHGE->Input_GetKeyState(HGEK_ESCAPE))
		return true;

	CoreInput();

	Vertex Force(1.0f, 0.0f);
	lpDynBody->ApplyForce(Force);
	lpDynBody->RotationOffset(0.1f);
	lpDynBody->Update();

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

	lpBackground->Render((float)WindowWidth, (float)WindowHeight);
	lpBody->Render();
	lpDynBody->Render();
	lpSprite->Render(10, 0x20);
	lpShip->Render();
	lpFont->Render(8, 8, HelpText);
	lpFont->RenderFPS(8, 250);

	lpHGE->Gfx_EndScene();

	return false;
}
