#include <tchar.h>
#include <hge.h>
#include "ErrExit.h"
#include "CoreSystem.h"

HGE* CoreGlobalHge = NULL;

//Needed for static OnRender
namespace{CoreSystem* CoreGlobalSystem;}

void CalculateAppSize(int& Width, int& Height);

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
	hge->Gfx_Clear(::CoreGlobalSystem->Config->BackGroundColor);
	RetVal = ::CoreGlobalSystem->RenderFunc();
	hge->Gfx_EndScene();
	return RetVal;
}

void CoreSystem::ReadConfig()
{
	Config->ReadFileINI();

	if(!Config->Width || !Config->Height)
		CalculateAppSize(Config->Width, Config->Height);
}

CoreSystem::CoreSystem(const char* Title, const CoreSystemFunc UpdateFunc, const CoreSystemFunc RenderFunc) : RenderFunc(RenderFunc)
{
	Stackit;

	Config = new CoreConfig();
	Trn(Config == NULL);

	Vault = new CoreResource();
	Trn(Vault == NULL);

	::CoreGlobalSystem = this;
	Try(Hge = hgeCreate(HGE_VERSION));
	CoreGlobalHge = Hge;
	Set_ErrExitHge_HgePtr(Hge);

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

void CalculateAppSize(int& Width, int& Height)
{
	//Size is 75% of screen size
	Width = int(GetSystemMetrics(SM_CXSCREEN) * 0.75);
	Height = int(GetSystemMetrics(SM_CYSCREEN) * 0.75);
}
