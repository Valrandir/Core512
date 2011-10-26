#pragma once
#include <hgevector.h>

struct Vertex : hgeVector
{
	Vertex();
	Vertex(float x, float y);

	void StabilizeEpsilon();
};
