#pragma once
#include <hge.h>
#include "CoreDefs.h"
#include "ErrExit.h"
#include "CoreResource.h"
#include "CoreTexture.h"
#include "CoreRotBody.h"

typedef bool (*CoreSystemFunc)();

class CoreSystem
{
	friend CoreSystem* CoreSystemCreate(const char* Title, const CoreSystemFunc UpdateFunc, const CoreSystemFunc RenderFunc);

	HGE* Hge;

	const CoreSystemFunc RenderFunc;
	void InitLogFile(const char* Title) const;
	static bool OnRender();

	CoreSystem(const char* Title, const CoreSystemFunc UpdateFunc, const CoreSystemFunc RenderFunc);

	public:
	CoreResource* Vault;

	~CoreSystem();

	void Execute() const;
	float Delta() const;
	CoreTexture* CoreTextureCreate(const char* ResPath) const;
	CoreDynBody* CoreDynBodyCreate(const CoreVector& Center, const CoreTexture& Texture) const;
	CoreRotBody* CoreRotBodyCreate(const CoreVector& Center, const CoreVector& Alignment, const CoreTexture& Texture) const;
	bool KeyState(int Key) const;
};
