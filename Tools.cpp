#include "Core512.h"
#include "Tools.h"

void RenderSquare(float x, float y, float size)
{
	hgeQuad Quad;

	QuadCreate(size, size, Quad);
	QuadOffset(x, y, Quad);

	Quad.v[0].col = 0xFF00FF00;
	Quad.v[1].col = 0xFFFFFF00;
	Quad.v[2].col = 0xFFFF0000;
	Quad.v[3].col = 0xFFFFFFFF;

	exHGE->Gfx_RenderQuad(&Quad);
}

void QuadCreate(float Width, float Height, hgeQuad& Quad)
{
	hgeVertex* ptr;
	int i;

	Quad.blend = BLEND_COLORADD | BLEND_ALPHABLEND;
	Quad.tex = NULL;

	for(i = 0, ptr = Quad.v; i < 4; i++, ptr++)
	{
		ptr->col = 0xFF000000;
		ptr->z = 0.5f;
	}

	ptr = Quad.v;

	ptr->x = 0;
	ptr->y = 0;
	ptr->tx = 0.0f;
	ptr->ty = 0.0f;

	++ptr;

	ptr->x = Width;
	ptr->y = 0;
	ptr->tx = 1.0f;
	ptr->ty = 0.0f;

	++ptr;

	ptr->x = Width;
	ptr->y = Height;
	ptr->tx = 1.0f;
	ptr->ty = 1.0f;

	++ptr;

	ptr->x = 0;
	ptr->y = Height;
	ptr->tx = 0.0f;
	ptr->ty = 1.0f;
}

void QuadSet(float x, float y, hgeQuad& Quad)
{
	hgeVertex* ptr;
	int i;

	float ox = x - Quad.v[0].x;
	float oy = y - Quad.v[0].y;

	for(i = 0, ptr = Quad.v; i < 4; i++, ptr++)
	{
		ptr->x += ox;
		ptr->y += oy;
	}
}

void QuadSetCenter(Vertex Center, hgeQuad& Quad)
{
	float w = Quad.v[1].x - Quad.v[0].x;
	float h = Quad.v[3].y - Quad.v[0].y;
	float cx = Center.x - w / 2;
	float cy = Center.y - h / 2;
	QuadSet(cx, cy, Quad);
}

void QuadOffset(float x, float y, hgeQuad& Quad)
{
	hgeVertex* ptr;
	int i;

	for(i = 0, ptr = Quad.v; i < 4; i++, ptr++)
	{
		ptr->x += x;
		ptr->y += y;
	}
}

float Abs(float val)
{
	return val > 0 ? val : -val;
}

//void QuadFromRect(Rect& r, hgeQuad& q)
//{
//	hgeVertex* v;
//
//	v = q.v;
//	v->x = r.x1; v->y = r.y1; v->z = 0.5f; v->col = 0xFF000000; v->tx = 0.0f; v->ty = 0.0f; ++v;
//	v->x = r.x2; v->y = r.y1; v->z = 0.5f; v->col = 0xFF000000; v->tx = 1.0f; v->ty = 0.0f; ++v;
//	v->x = r.x2; v->y = r.y2; v->z = 0.5f; v->col = 0xFF000000; v->tx = 1.0f; v->ty = 1.0f; ++v;
//	v->x = r.x1; v->y = r.y2; v->z = 0.5f; v->col = 0xFF000000; v->tx = 0.0f; v->ty = 1.0f;
//
//	q.blend = BLEND_COLORADD | BLEND_ALPHABLEND;
//	q.tex = NULL;
//}
