#include "../Core512.h"
#include "Body.h"

void QuadFromRect(Rect& r, hgeQuad& q);

Body::Body(Vertex Center, float Width, float Height)
{
	Rect.SetByCenter(Center.x, Center.y, Width, Height);
	QuadFromRect(Rect, Quad);
}

Body::Body(Vertex Center, HTEXTURE hTexture)
{
	float Width = (float)lpHGE->Texture_GetWidth(hTexture, true);
	float Height = (float)lpHGE->Texture_GetHeight(hTexture, true);
	Rect.SetByCenter(Center.x, Center.y, Width, Height);
	QuadFromRect(Rect, Quad);
	Quad.tex = hTexture;
}

void Body::Move(float cx, float cy)
{
	HTEXTURE hTex;
	Rect.Move(cx, cy);
	hTex = Quad.tex;
	QuadFromRect(Rect, Quad);
	Quad.tex = hTex;
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
