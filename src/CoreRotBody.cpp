#include "CoreDefs.h"
#include "CoreRotBody.h"

CoreRotBody::CoreRotBody(const CoreVector& Center, const CoreVector& Alignment, const CoreTexture& Texture) : CoreDynBody(Center, Texture)
{
	this->Alignment = Alignment;
	this->Alignment.StabilizeEpsilon();
	AlignmentDefault = this->Alignment;
}

CoreRotBody::~CoreRotBody()
{
}

void CoreRotBody::Turn(float RotationRadian)
{
	EpsilonStab(RotationRadian);
	if(!RotationRadian)
		return;

	CoreBody::RotationOffset(RotationRadian);

	Alignment = AlignmentDefault;
	Alignment.Rotate(CoreBody::RotationRadian);
	Alignment.StabilizeEpsilon();
}

void CoreRotBody::Thrust(float ThrustForce)
{
	ApplyForce(Alignment * ThrustForce);
}

void CoreRotBody::Update(float Delta)
{
	CoreDynBody::Update(Delta);
}
