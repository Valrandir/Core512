#include "CoreDefs.h"
#include "CoreRotBody.h"

void CoreRotBody::InitializeAlignment(const CoreVector& Alignment)
{
	this->Alignment = Alignment;
	this->Alignment.StabilizeEpsilon();
	AlignmentDefault = this->Alignment;
}

CoreRotBody::CoreRotBody() : Initialized(FALSE)
{
}

CoreRotBody::CoreRotBody(const CoreVector& Center, const CoreVector& Alignment, const CoreTexture& Texture) : CoreDynBody(Center, Texture), Initialized(TRUE)
{
	InitializeAlignment(Alignment);
}

void CoreRotBody::Initialize(const CoreVector& Center, const CoreVector& Alignment, const CoreTexture& Texture)
{
	Stackit;
	Trn(Initialized);

	CoreDynBody::Initialize(Center, Texture);
	InitializeAlignment(Alignment);

	Initialized = TRUE;
}

CoreRotBody::~CoreRotBody()
{
}

void CoreRotBody::Turn(float RotationRadian)
{
	Stackit;
	Try(Initialized);

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
	Stackit;
	Try(Initialized);

	ApplyForce(Alignment * ThrustForce);
}

void CoreRotBody::Update(float Delta)
{
	Stackit;
	Try(Initialized);

	CoreDynBody::Update(Delta);
}
