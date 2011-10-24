#include "../Core512.h"
#include "Body.h"

void Body::Init(Vertex Center, float Width, float Height, HTEXTURE hTexture)
{
	RotationRadian = 0.0f;
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
	float Width, Height;
	Texture::GetSize(hTexture, Width, Height, true);
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

void Body::RotationSet(float RotationRadian)
{
	if(RotationRadian < 0)
		RotationRadian = CoreRad1 + RotationRadian;

	if(RotationRadian > CoreRad1)
		RotationRadian = RotationRadian - CoreRad1;

	if(RotationRadian < 0 || RotationRadian > CoreRad1)
		RotationRadian = 0;

	this->RotationRadian = RotationRadian;
}

void Body::RotationOffset(float OffsetRadian)
{
	RotationSet(RotationRadian + OffsetRadian);
}

void Body::Move(float cx, float cy)
{
	Rect.Move(cx, cy);
}

void Body::Render()
{
	if(RotationRadian)
		lpSprite->RenderEx(Rect.cx, Rect.cy, RotationRadian);
	else
		lpSprite->Render(Rect.cx, Rect.cy);
}
