#include "CoreErrExit.h"
#include "CorePrimitive.h"

CorePrimitive::CorePrimitive(HGE* lpHge) : Hge(lpHge)
{
	Stackit;
	Trn(Hge == NULL);
}

void CorePrimitive::RenderLine(const CoreVector& xy1, const CoreVector& xy2, DWORD Color)
{
	Stackit;
	RenderLine(xy1.x, xy1.y, xy2.x, xy2.y, Color);
}

void CorePrimitive::RenderLine(float x1, float y1, float x2, float y2, DWORD Color)
{
	Stackit;
	Hge->Gfx_RenderLine(x1, y1, x2, y2, Color);
}

void CorePrimitive::RenderRect(const CoreRect& Rect, DWORD Color)
{
	Stackit;
	RenderRect(Rect.xy1.x, Rect.xy1.y, Rect.xy2.x, Rect.xy2.y, Color);
}

void CorePrimitive::RenderRect(float x1, float y1, float x2, float y2, DWORD Color)
{
	Stackit;
	int i = 0;
	hgeQuad Quad = {0};

	DWORD C1 = 0xFFFFFFFF;
	DWORD C2 = 0x00FFFFFF;

	Quad.blend = BLEND_DEFAULT;

	Quad.v[i].x = x1; Quad.v[i].y = y1; Quad.v[i].col = C1; ++i;
	Quad.v[i].x = x2; Quad.v[i].y = y1; Quad.v[i].col = C1; ++i;
	Quad.v[i].x = x2; Quad.v[i].y = y2; Quad.v[i].col = C2; ++i;
	Quad.v[i].x = x1; Quad.v[i].y = y2; Quad.v[i].col = C2; ++i;

/*
	Quad.v[i].x = x1; Quad.v[i].y = y1; Quad.v[i].col = Color; ++i;
	Quad.v[i].x = x2; Quad.v[i].y = y1; Quad.v[i].col = Color; ++i;
	Quad.v[i].x = x2; Quad.v[i].y = y2; Quad.v[i].col = Color; ++i;
	Quad.v[i].x = x1; Quad.v[i].y = y2; Quad.v[i].col = Color; ++i;
*/

	Hge->Gfx_RenderQuad(&Quad);
}
