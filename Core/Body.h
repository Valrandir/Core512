#pragma once
#include <hge.h>
#include "Vertex.h"

struct Body
{
	hgeQuad Quad;

	Body(Vertex Center, float Width, float Height);
	void Draw();
};
