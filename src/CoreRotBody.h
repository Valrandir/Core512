#pragma once
#include "CoreDynBody.h"

class CoreRotBody : public CoreDynBody
{
	CoreVector AlignmentDefault;
	CoreVector Alignment;

	public:
	CoreRotBody(const CoreVector& Center, const CoreVector& Alignment, const CoreTexture& Texture);
	virtual ~CoreRotBody();

	void Turn(float RotationRadian);
	void Thrust(float Force);
	void Update(float Delta);
};
