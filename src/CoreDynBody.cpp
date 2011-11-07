#include "CoreDefs.h"
#include "CoreDynBody.h"

float CoreDynBody::GlobalFriction = 0.97f;

CoreDynBody::CoreDynBody() : Initialized(FALSE)
{
}

CoreDynBody::CoreDynBody(const CoreVector& Center, const CoreTexture& Texture) : CoreBody(Center, Texture), Initialized(TRUE)
{
}

void CoreDynBody::Initialize(const CoreVector& Center, const CoreTexture& Texture)
{
	Stackit;
	Trn(Initialized);

	CoreBody::Initialize(Center, Texture);
	Initialized = TRUE;
}

CoreDynBody::~CoreDynBody()
{
}

void CoreDynBody::ApplyForce(const CoreVector& Force)
{
	Stackit;
	Try(Initialized);

	Velocity += Force;
}

void CoreDynBody::HardStop()
{
	Stackit;
	Try(Initialized);

	Velocity = 0;
}

void CoreDynBody::Update(float Delta)
{
	Stackit;
	Try(Initialized);

	CoreVector NewsPosition = CoreBody::CoreRect::Center;

	Velocity *= GlobalFriction;
	Velocity.StabilizeEpsilon();
	NewsPosition += Velocity * Delta;

	CoreBody::CoreRect::Move(NewsPosition);
}
