#pragma once
#include "CoreRotBody.h"

class Ship : public CoreRotBody
{
	float EngineForce;
	float TurnSpeed;

	public:
	Ship(const CoreVector& Center, const CoreTexture& Texture);
	void Turn(int RotateDirection, float Delta);
	void Thrust(int ForceDirection);
	void Update(float Delta);
	void Render();
};
