#pragma once
#include "CoreBody.h"

class CoreDynBody : public CoreBody
{
	BOOL Initialized;
	static float GlobalFriction;
	CoreVector Velocity;

	public:
	CoreDynBody();
	CoreDynBody(const CoreVector& Center, const CoreTexture& Texture);
	void Initialize(const CoreVector& Center, const CoreTexture& Texture);
	virtual ~CoreDynBody();

	virtual void ApplyForce(const CoreVector& Force);
	virtual void HardStop();
	virtual void Update(float Delta);
};
