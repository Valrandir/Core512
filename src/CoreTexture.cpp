#include "CoreDefs.h"
#include "CoreErrExit.h"
#include "CoreTexture.h"

CoreTexture::CoreTexture(const char* ResPath) : Width(w), Height(h), WidthF(wf), HeightF(hf), TextureHandle(hTexture)
{
	Stackit;

	TryH(hTexture = CoreSys.Hge->Texture_Load(ResPath));

	w = CoreSys.Hge->Texture_GetWidth(hTexture);
	h = CoreSys.Hge->Texture_GetHeight(hTexture);
	wf = (float)w;
	hf = (float)h;
}

CoreTexture::~CoreTexture()
{
	if(hTexture)
		CoreSys.Hge->Texture_Free(hTexture);
}

void CoreTexture::UseOriginalSize()
{
	w = CoreSys.Hge->Texture_GetWidth(hTexture, true);
	h = CoreSys.Hge->Texture_GetHeight(hTexture, true);
	wf = (float)w;
	hf = (float)h;
}
