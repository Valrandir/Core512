#include <hge.h>
#include "Body.h"

extern HGE* lpHGE;

void QuadFromRect(Rect& r, hgeQuad& q);

Body::Body(Vertex Center, float Width, float Height)
{
	Rect.SetByCenter(Center.x, Center.y, Width, Height);
	QuadFromRect(Rect, Quad);
}

void Body::SetTexture(HTEXTURE hTexture)
{
	Quad.tex = hTexture;
}

void Body::Draw()
{
	lpHGE->Gfx_RenderQuad(&Quad);
}

void QuadFromRect(Rect& r, hgeQuad& q)
{
	hgeVertex* v;

	v = q.v;
	v->x = r.x1; v->y = r.y1; v->z = 0.5f; v->col = 0xFF000000; v->tx = 0.0f; v->ty = 0.0f; ++v;
	v->x = r.x2; v->y = r.y1; v->z = 0.5f; v->col = 0xFF000000; v->tx = 1.0f; v->ty = 0.0f; ++v;
	v->x = r.x2; v->y = r.y2; v->z = 0.5f; v->col = 0xFF000000; v->tx = 1.0f; v->ty = 1.0f; ++v;
	v->x = r.x1; v->y = r.y2; v->z = 0.5f; v->col = 0xFF000000; v->tx = 0.0f; v->ty = 1.0f;

	q.blend = BLEND_COLORADD | BLEND_ALPHABLEND;
	q.tex = NULL;
}
