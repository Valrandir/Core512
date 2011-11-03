#include <tchar.h>
#include <hge.h>
#include "CoreErrExit.h"
#include "CoreSystem.h"

void CalculateAppSize(int& Width, int& Height);
CoreSystem* CoreSystem::Self = NULL;

void CoreSystemCreate(const char* Title, const CoreSystemFunc UpdateFunc, const CoreSystemFunc RenderFunc)
{
	static bool created = false;

	if(!created)
	{
		Stackit;
		//Call CoreSystemDestroy to unallocate
		Try(new CoreSystem(Title, UpdateFunc, RenderFunc));
		created = true;
	}
}

void CoreSystemDestroy()
{
	delete CoreSystem::Self;
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
	Stackit;
	bool RetVal;

	TryH(CoreSys.Hge->Gfx_BeginScene());

	CoreSys.Hge->Gfx_Clear(CoreSys.Config->BackGroundColor);
	RetVal = CoreSys.RenderFunc();
	CoreSys.Hge->Gfx_EndScene();

	return RetVal;
}

void CoreSystem::ReadConfig()
{
	Stackit;
	Config->ReadFileINI();

	if(!Config->Width || !Config->Height)
		CalculateAppSize(Config->Width, Config->Height);
}

CoreSystem::CoreSystem(const char* Title, const CoreSystemFunc UpdateFunc, const CoreSystemFunc RenderFunc) : RenderFunc(RenderFunc)
{
	Stackit;

	Self = this;
	Try(Hge = hgeCreate(HGE_VERSION));
	Set_ErrExitHge_HgePtr(Hge);

	Try(Config = new CoreConfig());
	ReadConfig();

	Hge->System_SetState(HGE_TITLE, Title);
	Hge->System_SetState(HGE_HIDEMOUSE, false);
	Hge->System_SetState(HGE_SHOWSPLASH, false);
	Hge->System_SetState(HGE_USESOUND, false);
	Hge->System_SetState(HGE_ICON, MAKEINTRESOURCE(100));

	Hge->System_SetState(HGE_WINDOWED, true);
	Hge->System_SetState(HGE_SCREENWIDTH, Config->Width);
	Hge->System_SetState(HGE_SCREENHEIGHT, Config->Height);
	Hge->System_SetState(HGE_SCREENBPP, 32);
	Hge->System_SetState(HGE_FPS, HGEFPS_VSYNC);

	Hge->System_SetState(HGE_FRAMEFUNC, UpdateFunc);
	Hge->System_SetState(HGE_RENDERFUNC, CoreSystem::OnRender);

	InitLogFile(Title);

	TryH(Hge->System_Initiate());
	Try(Vault = new CoreResource());
}

CoreSystem::~CoreSystem()
{
	DeleteNull(Vault);
	DeleteNull(Config);
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
	CoreTexture* Tex;
	Try(Tex = new CoreTexture(ResPath));
	return Tex;
}

CoreDynBody* CoreSystem::CoreDynBodyCreate(const CoreVector& Center, const CoreTexture& Texture) const
{
	Stackit;
	CoreDynBody* DynBody;
	Try(DynBody = new CoreDynBody(Center, Texture));
	return DynBody;
}

CoreRotBody* CoreSystem::CoreRotBodyCreate(const CoreVector& Center, const CoreVector& Alignment, const CoreTexture& Texture) const
{
	Stackit;
	CoreRotBody* RotBody;
	Try(RotBody = new CoreRotBody(Center, Alignment, Texture));
	return RotBody;
}

bool CoreSystem::KeyState(int Key) const
{
	return Hge->Input_GetKeyState(Key);
}

void CalculateAppSize(int& Width, int& Height)
{
	//Size is 75% of screen size
	Width = int(GetSystemMetrics(SM_CXSCREEN) * 0.75);
	Height = int(GetSystemMetrics(SM_CYSCREEN) * 0.75);
}
