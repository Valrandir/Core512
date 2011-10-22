#include "../Core512.h"
#include "Body.h"

Body::Body(Vertex Center, float Width, float Height)
{
	Rect.SetByCenter(Center.x, Center.y, Width, Height);
	lpSprite = new hgeSprite(NULL, 0, 0, Width, Height);
}

Body::Body(Vertex Center, HTEXTURE hTexture)
{
	float Width = (float)lpHGE->Texture_GetWidth(hTexture, true);
	float Height = (float)lpHGE->Texture_GetHeight(hTexture, true);
	Rect.SetByCenter(Center.x, Center.y, Width, Height);
	lpSprite = new hgeSprite(hTexture, 0, 0, Width, Height);
}

Body::~Body()
{
	DeleteNull(lpSprite)
}

void Body::Move(float cx, float cy)
{
	Rect.Move(cx, cy);
}

void Body::SetTexture(HTEXTURE hTexture)
{
	lpSprite->SetTexture(hTexture);
}

void Body::Draw()
{
	lpSprite->Render(Rect.x1, Rect.y1);
}
