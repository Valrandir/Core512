#pragma once
#include <hge.h>
#include <hgesprite.h>
#include "Rect.h"
#include "Vertex.h"

struct Body
{
	Rect Rect;
	hgeSprite* lpSprite;

	Body(Vertex Center, float Width, float Height);
	Body(Vertex Center, HTEXTURE hTexture);
	~Body();
	void Move(float cx, float cy);
	void SetTexture(HTEXTURE hTexture);
	void Draw();
};
