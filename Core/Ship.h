#pragma once
#include "DynBody.h"

class Ship : public DynBody
{
	HTEXTURE hTexture;

	public:
	float EngineForce;

	Ship(HTEXTURE hTexture);
	void Thrust(int dx, int dy);
	void Update();
	void Render();
};
