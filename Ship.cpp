#include <hge.h>
#include "Tools.h"
#include "Ship.h"

extern HGE* lpHGE;

HTEXTURE hTex;
hgeQuad Quad = {0};

void ShipInit()
{
	int Width, Height;

	hTex = lpHGE->Texture_Load("Res\\Ship.png");

	Width = lpHGE->Texture_GetWidth(hTex, true);
	Height = lpHGE->Texture_GetHeight(hTex, true);

	QuadCreate((float)Width, (float)Height, Quad);
	QuadOffset(10, 10, Quad);

	Quad.tex = hTex;
}

void ShipUnload()
{
	lpHGE->Texture_Free(hTex);
	hTex = NULL;
}

void ShipDraw()
{
	lpHGE->Gfx_RenderQuad(&Quad);
}
