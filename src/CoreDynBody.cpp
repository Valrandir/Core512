#include "CoreDynBody.h"

extern HGE* CoreGlobalHge;

float CoreDynBody::GlobalFriction = 0.97f;

CoreDynBody::CoreDynBody(const CoreVector& Center, const CoreTexture& Texture) : CoreBody(Center, Texture), Velocity(_Velocity)
{
}

void CoreDynBody::ApplyForce(const CoreVector& Force)
{
	_Velocity += Force;
}

void CoreDynBody::HardStop()
{
	_Velocity = 0;
}

void CoreDynBody::Update()
{
	float Delta = CoreGlobalHge->Timer_GetDelta();
	CoreVector NewsPosition = CoreBody::CoreRect::Center;

	_Velocity *= GlobalFriction;
	_Velocity.StabilizeEpsilon();
	NewsPosition += _Velocity * Delta;

	CoreBody::CoreRect::Move(NewsPosition);
}
