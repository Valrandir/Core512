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

CoreTexture* lpCoreTexture = NULL;
CoreDynBody* lpCoreDynBody = NULL;
CoreFlareList* lpCoreFlareList = NULL;
CoreZone* lpCoreZone = NULL;

HelpText* lpHelp;
Ship* lpShip = NULL;
CoreVector ScrollOffset;

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

	CoreSystemCreate("Corification", Update, Render);

	lpCoreTexture = CoreSys.Vault->LinkTexture("Res/Block.png");
	lpCoreDynBody = CoreSys.CoreDynBodyCreate(CoreVector(), *lpCoreTexture);

	Try(lpHelp = new HelpText());
	Try(lpShip = new Ship());
	Try(lpCoreZone = new CoreZone());

	lpCoreFlareList = new CoreFlareList();
	Try(lpCoreFlareList);
}

void Init()
{
	Stackit;

	CoreVector Force(500.0f, 250.0f);
	lpCoreDynBody->ApplyForce(Force);
	lpShip->CenterScreen();

	lpCoreZone->Add(*lpShip);
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
	DeleteNull(lpCoreDynBody)
	DeleteNull(lpCoreFlareList);
	DeleteNull(lpCoreZone);
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
		lpShip->CenterScreen();

	if(Command == CoreInput_Background_Toggle)
		lpCoreZone->ToggleBG();

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

	lpCoreDynBody->Update(Delta);
	lpCoreZone->Update(Delta);

	ScrollOffset.x = lpShip->CoreBody::Center.x - (float)(CoreSys.Config->Width >> 1);
	ScrollOffset.y = lpShip->CoreBody::Center.y - (float)(CoreSys.Config->Height >> 1);

	lpCoreFlareList->Update(Delta);

	return false;
}

bool Render()
{
	Stackit;
	lpCoreDynBody->Render();
	lpCoreZone->Render(ScrollOffset);
	lpCoreFlareList->Render();
	lpHelp->Render();
	return false;
}
