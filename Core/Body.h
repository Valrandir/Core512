#pragma once
#include <hge.h>
#include "Rect.h"
#include "Vertex.h"

struct Body
{
	Rect Rect;
	hgeQuad Quad;

	Body(Vertex Center, float Width, float Height);
	void SetTexture(HTEXTURE hTexture);
	void Draw();
};
