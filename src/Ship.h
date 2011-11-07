#pragma once
#include "CoreRotBody.h"

class Ship : public CoreRotBody
{
	float EngineForce;
	float TurnSpeed;

	public:
	Ship();
	void Turn(int RotateDirection, float Delta);
	void Thrust(int ForceDirection);
	void Update(float Delta);
	void Render();
	void CenterScreen();
};
