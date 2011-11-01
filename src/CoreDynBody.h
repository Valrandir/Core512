#pragma once
#include "CoreBody.h"

class CoreDynBody : public CoreBody
{
	static float GlobalFriction;
	CoreVector _Velocity;

	public:
	const CoreVector& Velocity;

	CoreDynBody(const CoreVector& Center, const CoreTexture& Texture);

	void ApplyForce(const CoreVector& Force);
	void HardStop();
	void Update();
};
