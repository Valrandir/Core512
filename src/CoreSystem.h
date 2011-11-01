#pragma once
#include <hge.h>
#include "CoreDefs.h"
#include "ErrExit.h"
#include "CoreTexture.h"
#include "CoreDynBody.h"

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
	~CoreSystem();

	void Execute() const;
	CoreTexture* CoreSystem::CoreTextureCreate(const char* ResPath) const;
	CoreDynBody* CoreSystem::CoreDynBodyCreate(const CoreTexture& Texture) const;
};
