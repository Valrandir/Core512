#pragma once
#include "CoreDynBody.h"

class CoreRotBody : public CoreDynBody
{
	CoreVector AlignmentDefault;
	CoreVector Alignment;

	public:
	CoreRotBody(const CoreVector& Center, const CoreVector& Alignment, const CoreTexture& Texture);
	virtual ~CoreRotBody();

	virtual void Turn(float RotationRadian);
	virtual void Thrust(float Force);
	virtual void Update(float Delta);
};
