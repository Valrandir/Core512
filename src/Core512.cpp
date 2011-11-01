#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "CoreSystem.h"
#include "CoreDynBody.h"

void Load();
void Init();
void Execute();
void Unload();
bool Update();
bool Render();

CoreSystem* lpCoreSystem = NULL;
CoreTexture* lpCoreTexture = NULL;
CoreDynBody* lpCoreDynBody = NULL;

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
	lpCoreSystem = CoreSystemCreate("Corification", Update, Render);
	lpCoreTexture = lpCoreSystem->CoreTextureCreate("Res/Block.png");
	lpCoreDynBody = lpCoreSystem->CoreDynBodyCreate(*lpCoreTexture);
	lpCoreDynBody->Move(CoreVector(50, 50));
}

void Init()
{
	Stackit;
	CoreVector Force(500.0f, 50.0f);
	lpCoreDynBody->ApplyForce(Force);
}

void Execute()
{
	Stackit;
	lpCoreSystem->Execute();
}

void Unload()
{
	Stackit;
	DeleteNull(lpCoreTexture)
	DeleteNull(lpCoreSystem)
	DeleteNull(lpCoreDynBody)
}

bool Update()
{
	Stackit;

	lpCoreDynBody->Update();
	return false;
}

bool Render()
{
	Stackit;
	lpCoreDynBody->Render();
	return false;
}
