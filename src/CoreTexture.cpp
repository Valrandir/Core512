#include "CoreErrExit.h"
#include "CoreTexture.h"

extern HGE* CoreGlobalHge;

CoreTexture::CoreTexture(const char* ResPath) : Width(w), Height(h), WidthF(wf), HeightF(hf), TextureHandle(hTexture)
{
	Stackit;

	TryH(hTexture = CoreGlobalHge->Texture_Load(ResPath));

	w = CoreGlobalHge->Texture_GetWidth(hTexture);
	h = CoreGlobalHge->Texture_GetHeight(hTexture);
	wf = (float)w;
	hf = (float)h;
}

CoreTexture::~CoreTexture()
{
	if(hTexture)
		CoreGlobalHge->Texture_Free(hTexture);
}
