#include "Vertex.h"

#define Abs(val)((val) > 0 ? (val) : -(val))

Vertex::Vertex() : x(0.0f), y(0.0f)
{
}

Vertex::Vertex(float x, float y) : x(x), y(y)
{
}

void Vertex::StabilizeEpsilon()
{
	const float Epsilon = 0.01f;
	if(x && Abs(x) < Epsilon)
		x = 0;

	if(y && Abs(y) < Epsilon)
		y = 0;
}
