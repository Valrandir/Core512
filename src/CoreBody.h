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

	void RotationSet(float RotationRadian);
	void RotationOffset(float OffsetRadian);
	void Move(const CoreVector& Center);
	void Render();
};

