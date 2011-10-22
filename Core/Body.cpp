#include "../Core512.h"
#include "Body.h"

void Body::Init(Vertex Center, float Width, float Height, HTEXTURE hTexture)
{
	RotationGradient = 0.0f;
	Rect.SetByCenter(Center.x, Center.y, Width, Height);
	lpSprite = new hgeSprite(hTexture, 0, 0, Width, Height);
	lpSprite->SetHotSpot(Width / 2, Height / 2);
}

Body::Body(Vertex Center, float Width, float Height)
{
	Init(Center, Width, Height, NULL);
}

Body::Body(Vertex Center, HTEXTURE hTexture)
{
	float Width = (float)lpHGE->Texture_GetWidth(hTexture, true);
	float Height = (float)lpHGE->Texture_GetHeight(hTexture, true);
	Init(Center, Width, Height, hTexture);
}

Body::~Body()
{
	DeleteNull(lpSprite)
}

void Body::TextureSet(HTEXTURE hTexture)
{
	lpSprite->SetTexture(hTexture);
}

void Body::RotationSet(float RotationGradient)
{

	if(RotationGradient < 0 || RotationGradient > CorePI2)
		RotationGradient = 0;

	this->RotationGradient = RotationGradient;
}

void Body::RotationOffset(float OffsetGradient)
{
	RotationSet(RotationGradient + OffsetGradient);
}

void Body::Move(float cx, float cy)
{
	Rect.Move(cx, cy);
}

void Body::Render()
{
	if(RotationGradient)
		lpSprite->RenderEx(Rect.x1, Rect.y1, RotationGradient);
	else
		lpSprite->Render(Rect.x1, Rect.y1);
}
