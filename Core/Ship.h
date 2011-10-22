#pragma once
#include "DynBody.h"

class Ship : public DynBody
{
	HTEXTURE hTexture;

	public:
	float EngineForce;
	Vertex Alignment;

	Ship(HTEXTURE hTexture);
	void Align(Vertex Alignment);
	void Turn(int dRotate);
	void Thrust(int dx, int dy);
	void Update();
	void Render();
};
