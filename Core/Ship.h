#pragma once
#include "DynBody.h"

class Ship : public DynBody
{
	HTEXTURE hTexture;

	public:
	float EngineForce;
	Vertex Alignment;

	Ship(HTEXTURE hTexture);
	void Turn(int dRotate);
	void Thrust(int ForceDirection);
	void Update();
	void Render();
};
