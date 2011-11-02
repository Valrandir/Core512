#include "Ship.h"

Ship::Ship(const CoreVector& Center, const CoreTexture& Texture) : CoreRotBody(Center, CoreVector(0.0f, -1.0f), Texture)
{
	EngineForce = 100.0f;
	TurnSpeed = 10.0f;
}

void Ship::Turn(int RotateDirection, float Delta)
{
	CoreRotBody::Turn(RotateDirection * TurnSpeed * Delta);
}

void Ship::Thrust(int ForceDirection)
{
	CoreRotBody::Thrust(ForceDirection * EngineForce);
}

void Ship::Update(float Delta)
{
	CoreRotBody::Update(Delta);
}

void Ship::Render()
{
	CoreBody::Render();
	//CoreBody* b = new CoreBody(CoreVector(100, 100), CoreTexture("Res/Ship.png"));
	//b->Render();
}
