#include "CoreErrExit.h"
#include "CorePrimitive.h"

CorePrimitive::CorePrimitive(HGE* lpHge) : Hge(lpHge)
{
	Stackit;
	Try(Hge);
}

void CorePrimitive::RenderLine(const CoreVector& xy1, const CoreVector& xy2, DWORD Color) const
{
	Stackit;
	RenderLine(xy1.x, xy1.y, xy2.x, xy2.y, Color);
}

void CorePrimitive::RenderLine(float x1, float y1, float x2, float y2, DWORD Color) const
{
	Stackit;
	Hge->Gfx_RenderLine(x1, y1, x2, y2, Color);
}

void CorePrimitive::RenderRect(const CoreRect& Rect, DWORD Color) const
{
	Stackit;
	RenderRect(Rect.xy1.x, Rect.xy1.y, Rect.xy2.x, Rect.xy2.y, Color);
}

void CorePrimitive::RenderRect(float x1, float y1, float x2, float y2, DWORD Color) const
{
	Stackit;
	int i = 0;
	hgeQuad Quad = {0};

	Quad.blend = BLEND_DEFAULT;
	Quad.v[i].x = x1; Quad.v[i].y = y1; Quad.v[i].col = Color; ++i;
	Quad.v[i].x = x2; Quad.v[i].y = y1; Quad.v[i].col = Color; ++i;
	Quad.v[i].x = x2; Quad.v[i].y = y2; Quad.v[i].col = Color; ++i;
	Quad.v[i].x = x1; Quad.v[i].y = y2; Quad.v[i].col = Color; ++i;

	Hge->Gfx_RenderQuad(&Quad);
}

void CorePrimitive::RenderGradient(const CoreRect& Rect, DWORD Colors[4]) const
{
	Stackit;
	RenderGradient(Rect.xy1.x, Rect.xy1.y, Rect.xy2.x, Rect.xy2.y, Colors);
}

void CorePrimitive::RenderGradient(float x1, float y1, float x2, float y2, DWORD Colors[4]) const
{
	Stackit;
	int i = 0;
	hgeQuad Quad = {0};

	Quad.blend = BLEND_DEFAULT;

	Quad.v[i].x = x1; Quad.v[i].y = y1; Quad.v[i].col = Colors[i]; ++i;
	Quad.v[i].x = x2; Quad.v[i].y = y1; Quad.v[i].col = Colors[i]; ++i;
	Quad.v[i].x = x2; Quad.v[i].y = y2; Quad.v[i].col = Colors[i]; ++i;
	Quad.v[i].x = x1; Quad.v[i].y = y2; Quad.v[i].col = Colors[i]; ++i;

	Hge->Gfx_RenderQuad(&Quad);
}
