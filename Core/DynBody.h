#pragma once
#include "Body.h"

struct DynBody : public Body
{
	Vertex Velocity;

	DynBody(Vertex Center, float Width, float Height);
	DynBody(Vertex Center, HTEXTURE hTexture);

	void ApplyForce(Vertex Force);
	void Update();
};
