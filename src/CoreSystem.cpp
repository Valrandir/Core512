#include <tchar.h>
#include <hge.h>
#include "ErrExit.h"
#include "CoreSystem.h"

HGE* CoreGlobalHge = NULL;

//Needed for static OnRender
namespace{CoreSystem* lpCoreSystem;}

CoreSystem* CoreSystemCreate(const char* Title, const CoreSystemFunc UpdateFunc, const CoreSystemFunc RenderFunc)
{
	Stackit;
	CoreSystem* lpCoreSystem = new CoreSystem(Title, UpdateFunc, RenderFunc);
	Trn(lpCoreSystem == NULL);
	return lpCoreSystem;
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
	HGE* hge = ::lpCoreSystem->Hge;
	TryH(hge->Gfx_BeginScene());
	hge->Gfx_Clear(0xFF808080);
	RetVal = ::lpCoreSystem->RenderFunc();
	hge->Gfx_EndScene();
	return RetVal;
}

CoreSystem::CoreSystem(const char* Title, const CoreSystemFunc UpdateFunc, const CoreSystemFunc RenderFunc) : RenderFunc(RenderFunc)
{
	Stackit;

	::lpCoreSystem = this;
	Try(Hge = hgeCreate(HGE_VERSION));
	CoreGlobalHge = Hge;
	Set_ErrExitHge_HgePtr(Hge);

	Hge->System_SetState(HGE_TITLE, Title);
	Hge->System_SetState(HGE_HIDEMOUSE, false);
	Hge->System_SetState(HGE_SHOWSPLASH, false);
	Hge->System_SetState(HGE_USESOUND, false);

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
	Hge->System_Shutdown();
	Hge->Release();
}

void CoreSystem::Execute() const
{
	Stackit;
	TryH(Hge->System_Start());
}

CoreTexture* CoreSystem::CoreTextureCreate(const char* ResPath) const
{
	Stackit;
	CoreTexture* Tex;

	Tex = new CoreTexture(ResPath);
	Trn(Tex == NULL);

	return Tex;
}

CoreDynBody* CoreSystem::CoreDynBodyCreate(const CoreTexture& Texture) const
{
	Stackit;
	CoreDynBody* DynBody;

	DynBody = new CoreDynBody(CoreVector(), Texture);
	Trn(DynBody == NULL);

	return DynBody;
}
