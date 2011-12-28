#pragma once
#include <hge.h>
#include "CoreDefs.h"
#include "CoreErrExit.h"
#include "CoreConfig.h"
#include "CoreResource.h"
#include "CoreTexture.h"
#include "CoreSprite.h"
#include "CoreRotBody.h"
#include "CorePrimitive.h"

#define CoreSys (*CoreSystem::Self)
typedef bool (*CoreSystemFunc)();

class CoreSystem
{
	friend void CoreSystemCreate(const char* Title, const CoreSystemFunc UpdateFunc, const CoreSystemFunc RenderFunc);
	friend void CoreSystemDestroy();

	const CoreSystemFunc RenderFunc;
	void InitLogFile(const char* Title) const;
	static bool OnRender();
	void ReadConfig();
	bool IsClipping;

	CoreSystem(const char* Title, const CoreSystemFunc UpdateFunc, const CoreSystemFunc RenderFunc);

	public:
	static CoreSystem* Self;
	CoreConfig* Config;
	CoreResource* Vault;
	CorePrimitive* Draw;
	HGE* Hge;

	~CoreSystem();

	void Execute() const;
	float Delta() const;
	void ClearScreen() const;
	void ClearScreen(DWORD Color) const;
	void GetScreenSize(CoreVector& ScrSize);
	CoreTexture* CoreTextureCreate(const char* ResPath) const;
	CoreSprite* CoreSpriteCreate(const CoreTexture& Texture, bool CenterHotSpot = true) const;
	CoreBody* CoreBodyCreate(const CoreVector& Center, const CoreTexture& Texture) const;
	CoreDynBody* CoreDynBodyCreate(const CoreVector& Center, const CoreTexture& Texture) const;
	CoreRotBody* CoreRotBodyCreate(const CoreVector& Center, const CoreVector& Alignment, const CoreTexture& Texture) const;
	void ClipReset();
	void Clip(const CoreRect& Rect);
	bool KeyState(int Key) const;
};
