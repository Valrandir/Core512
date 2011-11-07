#pragma once
#include "CoreDynBody.h"

class CoreRotBody : public CoreDynBody
{
	BOOL Initialized;
	CoreVector AlignmentDefault;
	CoreVector Alignment;

	void InitializeAlignment(const CoreVector& Alignment);

	public:
	CoreRotBody();
	CoreRotBody(const CoreVector& Center, const CoreVector& Alignment, const CoreTexture& Texture);
	void Initialize(const CoreVector& Center, const CoreVector& Alignment, const CoreTexture& Texture);
	virtual ~CoreRotBody();

	virtual void Turn(float RotationRadian);
	virtual void Thrust(float Force);
	virtual void Update(float Delta);
};
