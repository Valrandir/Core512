#pragma once
#include <hge.h>
#include <hgesprite.h>
#include "Rect.h"
#include "Vertex.h"

struct Body
{
	float RotationGradient;
	Rect Rect;
	hgeSprite* lpSprite;

	void Init(Vertex Center, float Width, float Height, HTEXTURE hTexture);
	Body(Vertex Center, float Width, float Height);
	Body(Vertex Center, HTEXTURE hTexture);
	~Body();

	void TextureSet(HTEXTURE hTexture);
	void RotationSet(float RotationGradient);
	void RotationOffset(float OffsetGradient);
	void Move(float cx, float cy);
	void Render();
};
