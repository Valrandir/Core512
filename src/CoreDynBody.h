#pragma once
#include "CoreBody.h"

class CoreDynBody : public CoreBody
{
	static float GlobalFriction;
	CoreVector Velocity;

	public:
	CoreDynBody(const CoreVector& Center, const CoreTexture& Texture);
	virtual ~CoreDynBody();

	void ApplyForce(const CoreVector& Force);
	void HardStop();
	void Update(float Delta);
};
