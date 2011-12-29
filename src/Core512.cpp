#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "CoreSystem.h"
#include "CoreInput.h"
#include "CoreFlareList.h"
#include "CoreZone.h"
#include "HelpText.h"
#include "Ship.h"

void Load();
void Init();
void Execute();
void Unload();
void UpdateInput(float Delta);
bool Update();
bool Render();

CoreBody* lpCoreBody[3];
CoreFlareList* lpCoreFlareList = NULL;
CoreZone* lpCoreZone = NULL;
CoreMusic* lpCoreMusic = NULL;

HelpText* lpHelp;
Ship* lpShip = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	Stackit;

	Load();
	Init();
	Execute();
	Unload();

	return 0;
}

void Load()
{
	Stackit;
	CoreTexture* lpCoreTexture = NULL;

	CoreSystemCreate("Corification", Update, Render);

	lpCoreTexture = CoreSys.Vault->LinkTexture("Res/Block.png");
	lpCoreBody[0] = CoreSys.CreateCoreBody(CoreVector(-100.0f, 50.0f), *lpCoreTexture);
	lpCoreBody[1] = CoreSys.CreateCoreBody(CoreVector(-50.0f, -50.0f), *lpCoreTexture);
	lpCoreBody[2] = CoreSys.CreateCoreBody(CoreVector(100.0f, 50.0f), *lpCoreTexture);

	Try(lpHelp = new HelpText());
	Try(lpShip = new Ship());
	Try(lpCoreZone = new CoreZone(CoreVector(0x1000, 0x1000)));
	Try(lpCoreFlareList = new CoreFlareList());

	Try(lpCoreMusic = new CoreMusic());
	lpCoreMusic->Play();
}

void Init()
{
	Stackit;

	lpCoreZone->Add(*lpCoreBody[0]);
	lpCoreZone->Add(*lpCoreBody[1]);
	lpCoreZone->Add(*lpCoreBody[2]);
	lpCoreZone->Add(*lpShip);
	lpCoreZone->TrackBody(*lpShip);
}

void Execute()
{
	Stackit;
	CoreSys.Execute();
}

void Unload()
{
	Stackit;
	DeleteNull(lpHelp);
	DeleteNull(lpCoreFlareList);
	DeleteNull(lpCoreZone);
	DeleteNull(lpCoreMusic);
	CoreSystemDestroy();
}

void UpdateInput(float Delta)
{
	int ForceDirection, RotateDirection;
	int Command;

	CoreInput::Direction(ForceDirection, RotateDirection);
	Command = CoreInput::Command();

	if(RotateDirection)
		lpShip->Turn(RotateDirection, Delta);

	if(ForceDirection)
		lpShip->Thrust(ForceDirection);

	if(Command == CoreInput_ShipReset)
	{
		lpShip->CenterScreen();
		lpCoreZone->TrackBody(*lpShip);
	}

	if(Command == CoreInput_Background_Toggle)
		lpCoreZone->ToggleBG();

	if(Command == CoreInput_Music_Toggle)
		lpCoreMusic->Toggle();

	if(Command == CoreInput_Explode)
		lpCoreFlareList->Add(lpShip->Center, "Res/Explosion.png", 5, 5);
}

bool Update()
{
	Stackit;
	float Delta;

	if(CoreSys.KeyState(HGEK_ESCAPE))
		return true;

	Delta = CoreSys.Delta();
	UpdateInput(Delta);

	lpCoreZone->Update(Delta);

	lpCoreFlareList->Update(Delta);

	return false;
}

bool Render()
{
	Stackit;
	lpCoreZone->Render();
	lpCoreFlareList->Render(lpCoreZone->GetOffset());
	lpHelp->Render();
	return false;
}
