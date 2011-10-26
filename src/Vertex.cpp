#include "Vertex.h"

#define Abs(val)((val) > 0 ? (val) : -(val))

Vertex::Vertex() : hgeVector() {}
Vertex::Vertex(float x, float y) : hgeVector(x, y) {}

void Vertex::StabilizeEpsilon()
{
	const float Epsilon = 0.01f;
	if(x && Abs(x) < Epsilon)
		x = 0;

	if(y && Abs(y) < Epsilon)
		y = 0;
}
