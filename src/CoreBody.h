#pragma once
#include <hgesprite.h>
#include "CoreRect.h"
#include "CoreTexture.h"

class CoreBody : public CoreRect
{
	float _RotationRadian;
	hgeSprite* lpSprite;

	public:
	const float& RotationRadian;

	CoreBody(const CoreVector& Center, const CoreTexture& Texture);
	virtual ~CoreBody();

	virtual void RotationSet(float RotationRadian);
	virtual void RotationOffset(float OffsetRadian);
	virtual void Move(const CoreVector& Center);
	virtual void Render();
};

