#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "CoreSystem.h"
#include "CoreInput.h"
#include "CoreBackground.h"

void Load();
void Init();
void Execute();
void Unload();
void UpdateInput(float Delta);
bool Update();
bool Render();

CoreTexture* lpCoreTexture = NULL;
CoreDynBody* lpCoreDynBody = NULL;
CoreBackground* lpCoreBackground = NULL;

#include "HelpText.h"
#include "Ship.h"

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

	lpCoreBackground = new CoreBackground();

	lpCoreTexture = CoreSys.Vault->LinkTexture("Res/Block.png");
	lpCoreDynBody = CoreSys.CoreDynBodyCreate(CoreVector(), *lpCoreTexture);

	Try(lpHelp = new HelpText());
	Try(lpShip = new Ship());
}

void Init()
{
	Stackit;

	CoreVector Force(500.0f, 250.0f);
	lpCoreDynBody->ApplyForce(Force);

	lpShip->CenterScreen();
}

void Execute()
{
	Stackit;
	CoreSys.Execute();
}

void Unload()
{
	Stackit;
	DeleteNull(lpShip);
	DeleteNull(lpHelp);
	DeleteNull(lpCoreDynBody)
	DeleteNull(lpCoreBackground);
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
		lpCoreBackground->Toggle();
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
	lpShip->Update(Delta);

	ScrollOffset.x = lpShip->CoreBody::Center.x - (float)(CoreSys.Config->Width >> 1);
	ScrollOffset.y = lpShip->CoreBody::Center.y - (float)(CoreSys.Config->Height >> 1);

	return false;
}

bool Render()
{
	Stackit;
	lpCoreBackground->RenderMosaic(ScrollOffset);
	lpCoreDynBody->Render();
	lpShip->Render();
	lpHelp->Render();
	return false;
}
