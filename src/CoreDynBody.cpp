#include "CoreDefs.h"
#include "CoreDynBody.h"

extern HGE* CoreGlobalHge;

float CoreDynBody::GlobalFriction = 0.97f;

CoreDynBody::CoreDynBody(const CoreVector& Center, const CoreTexture& Texture) : CoreBody(Center, Texture)
{
}

CoreDynBody::~CoreDynBody()
{
}

void CoreDynBody::ApplyForce(const CoreVector& Force)
{
	Velocity += Force;
}

void CoreDynBody::HardStop()
{
	Velocity = 0;
}

void CoreDynBody::Update(float Delta)
{
	CoreVector NewsPosition = CoreBody::CoreRect::Center;

	Velocity *= GlobalFriction;
	Velocity.StabilizeEpsilon();
	NewsPosition += Velocity * Delta;

	CoreBody::CoreRect::Move(NewsPosition);
}
