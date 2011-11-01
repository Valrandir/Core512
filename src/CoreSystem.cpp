#include <tchar.h>
#include <hge.h>
#include "ErrExit.h"
#include "CoreSystem.h"

HGE* CoreGlobalHge = NULL;

//Needed for static OnRender
namespace{CoreSystem* CoreGlobalSystem;}

CoreSystem* CoreSystemCreate(const char* Title, const CoreSystemFunc UpdateFunc, const CoreSystemFunc RenderFunc)
{
	Stackit;
	CoreSystem* CoreGlobalSystem = new CoreSystem(Title, UpdateFunc, RenderFunc);
	Trn(CoreGlobalSystem == NULL);
	return CoreGlobalSystem;
}

void CoreSystem::InitLogFile(const char* Title) const
{
	#ifdef _DEBUG
		char LogFile[MAX_PATH];
		_tcscpy_s(LogFile, MAX_PATH, Title);
		_tcscat_s(LogFile, MAX_PATH, ".Log.txt");
		Hge->System_SetState(HGE_LOGFILE, LogFile);
	#endif
}

bool CoreSystem::OnRender()
{
	bool RetVal;
	HGE* hge = ::CoreGlobalSystem->Hge;
	TryH(hge->Gfx_BeginScene());
	hge->Gfx_Clear(0xFF808080);
	RetVal = ::CoreGlobalSystem->RenderFunc();
	hge->Gfx_EndScene();
	return RetVal;
}

CoreSystem::CoreSystem(const char* Title, const CoreSystemFunc UpdateFunc, const CoreSystemFunc RenderFunc) : RenderFunc(RenderFunc)
{
	Stackit;

	Vault = new CoreResource();
	Trn(Vault == NULL);

	::CoreGlobalSystem = this;
	Try(Hge = hgeCreate(HGE_VERSION));
	CoreGlobalHge = Hge;
	Set_ErrExitHge_HgePtr(Hge);

	Hge->System_SetState(HGE_TITLE, Title);
	Hge->System_SetState(HGE_HIDEMOUSE, false);
	Hge->System_SetState(HGE_SHOWSPLASH, false);
	Hge->System_SetState(HGE_USESOUND, false);
	Hge->System_SetState(HGE_ICON, MAKEINTRESOURCE(100));

	Hge->System_SetState(HGE_WINDOWED, true);
	Hge->System_SetState(HGE_SCREENWIDTH, 320);
	Hge->System_SetState(HGE_SCREENHEIGHT, 240);
	Hge->System_SetState(HGE_SCREENBPP, 32);
	Hge->System_SetState(HGE_FPS, HGEFPS_VSYNC);

	Hge->System_SetState(HGE_FRAMEFUNC, UpdateFunc);
	Hge->System_SetState(HGE_RENDERFUNC, CoreSystem::OnRender);

	InitLogFile(Title);

	TryH(Hge->System_Initiate());
}

CoreSystem::~CoreSystem()
{
	DeleteNull(Vault);
	Hge->System_Shutdown();
	Hge->Release();
}

void CoreSystem::Execute() const
{
	Stackit;
	TryH(Hge->System_Start());
}

float CoreSystem::Delta() const
{
	return Hge->Timer_GetDelta();
}

CoreTexture* CoreSystem::CoreTextureCreate(const char* ResPath) const
{
	Stackit;
	CoreTexture* Tex = new CoreTexture(ResPath);
	Trn(Tex == NULL);
	return Tex;
}

CoreDynBody* CoreSystem::CoreDynBodyCreate(const CoreVector& Center, const CoreTexture& Texture) const
{
	Stackit;
	CoreDynBody* DynBody = new CoreDynBody(Center, Texture);
	Trn(DynBody == NULL);
	return DynBody;
}

CoreRotBody* CoreSystem::CoreRotBodyCreate(const CoreVector& Center, const CoreVector& Alignment, const CoreTexture& Texture) const
{
	Stackit;
	CoreRotBody* RotBody = new CoreRotBody(Center, Alignment, Texture);
	Trn(RotBody == NULL);
	return RotBody;
}

bool CoreSystem::KeyState(int Key) const
{
	return Hge->Input_GetKeyState(Key);
}
