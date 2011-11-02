#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "CoreSystem.h"
#include "CoreInput.h"

void Load();
void Init();
void Execute();
void Unload();
void UpdateInput(float Delta);
bool Update();
bool Render();

CoreSystem* CoreGlobalSystem = NULL;
CoreTexture* lpCoreTexture = NULL;
CoreDynBody* lpCoreDynBody = NULL;

#include "HelpText.h"
#include "Ship.h"

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

	CoreGlobalSystem = CoreSystemCreate("Corification", Update, Render);

	lpCoreTexture = CoreGlobalSystem->Vault->LinkTexture("Res/Block.png");
	lpCoreDynBody = CoreGlobalSystem->CoreDynBodyCreate(CoreVector(), *lpCoreTexture);

	Try(lpHelp = new HelpText());

	lpCoreTexture = CoreGlobalSystem->Vault->LinkTexture("Res/Ship.png");
	Try(lpShip = new Ship(CoreVector(), *lpCoreTexture));
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
	CoreGlobalSystem->Execute();
}

void Unload()
{
	Stackit;
	DeleteNull(lpShip);
	DeleteNull(lpHelp);
	DeleteNull(lpCoreDynBody)
	DeleteNull(CoreGlobalSystem)
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
}

bool Update()
{
	Stackit;
	float Delta;

	if(CoreGlobalSystem->KeyState(HGEK_ESCAPE))
		return true;

	Delta = CoreGlobalSystem->Delta();
	UpdateInput(Delta);

	lpCoreDynBody->Update(Delta);
	lpShip->Update(Delta);
	return false;
}

bool Render()
{
	Stackit;
	lpCoreDynBody->Render();
	lpShip->Render();
	lpHelp->Render();
	return false;
}
