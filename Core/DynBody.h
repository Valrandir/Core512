#pragma once
#include "Body.h"

struct DynBody : public Body
{
	static float GlobalFriction;
	Vertex Velocity;

	DynBody(Vertex Center, float Width, float Height);
	DynBody(Vertex Center, HTEXTURE hTexture);

	void ApplyForce(Vertex Force);
	void HardStop();
	void Update();
};
