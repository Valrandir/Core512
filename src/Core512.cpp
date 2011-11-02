#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "CoreSystem.h"
#include "CoreInput.h"
#include "CoreRotBody.h"

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
CoreRotBody* lpCoreRotBody = NULL;

#include "HelpText.h"
HelpText* lpHelp;

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
	lpCoreRotBody = CoreGlobalSystem->CoreRotBodyCreate(CoreVector(25, 25), CoreVector(1, 0), *lpCoreTexture);

	Try(lpHelp = new HelpText());
}

void Init()
{
	Stackit;
	CoreVector Force(500.0f, 250.0f);
	lpCoreDynBody->ApplyForce(Force);
}

void Execute()
{
	Stackit;
	CoreGlobalSystem->Execute();
}

void Unload()
{
	Stackit;
	DeleteNull(lpHelp);
	DeleteNull(lpCoreDynBody)
	DeleteNull(lpCoreRotBody)
	DeleteNull(CoreGlobalSystem)
}

void UpdateInput(float Delta)
{
	int ForceDirection, RotateDirection;
	CoreInput::Direction(ForceDirection, RotateDirection);

	if(RotateDirection)
		lpCoreRotBody->Turn(RotateDirection * Delta * 10.0f);

	if(ForceDirection)
		lpCoreRotBody->Thrust(ForceDirection * 50.0f);
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
	lpCoreRotBody->Update(Delta);
	return false;
}

bool Render()
{
	Stackit;
	lpCoreDynBody->Render();
	lpCoreRotBody->Render();
	lpHelp->Render();
	return false;
}
