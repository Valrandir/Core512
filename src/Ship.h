#pragma once
#include "CoreRotBody.h"
#include "CoreTimer.h"
#include "ShipParticle.h"

class CoreZone;

class Ship : public CoreRotBody
{
	float EngineForce;
	float TurnSpeed;
	CoreTimer Timer;
	ShipParticle* lpParticle[2];

	void UpdateParticle();

	public:
	Ship();
	~Ship();
	void Turn(int RotateDirection, float Delta);
	void Thrust(int ForceDirection);
	void Shoot();
	void Update(float Delta);
	void CenterScreen();
	void Render() const;
	void Render(const CoreVector& Offset) const;
};
