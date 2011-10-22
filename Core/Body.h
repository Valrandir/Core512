#pragma once
#include <hge.h>
#include <hgesprite.h>
#include "Rect.h"
#include "Vertex.h"

struct Body
{
	float RotationRadian;
	Rect Rect;
	hgeSprite* lpSprite;

	void Init(Vertex Center, float Width, float Height, HTEXTURE hTexture);
	Body(Vertex Center, float Width, float Height);
	Body(Vertex Center, HTEXTURE hTexture);
	~Body();

	void TextureSet(HTEXTURE hTexture);
	void RotationSet(float RotationRadian);
	void RotationOffset(float OffsetRadian);
	void Move(float cx, float cy);
	void Render();
};
