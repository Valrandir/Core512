#pragma once
#include "CoreRotBody.h"
#include "ShipParticle.h"
class CoreZone;

class Ship : public CoreRotBody
{
	CoreZone& CoreZoneRef;
	float EngineForce;
	float TurnSpeed;
	ShipParticle* lpParticle[2];

	void UpdateParticle();

	public:
	Ship(CoreZone& CoreZoneRef);
	~Ship();
	void Turn(int RotateDirection, float Delta);
	void Thrust(int ForceDirection);
	void Shoot();
	void Update(float Delta);
	void CenterScreen();
	void Render() const;
	void Render(const CoreVector& Offset) const;
};
