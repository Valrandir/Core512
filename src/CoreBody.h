#pragma once
#include <hgesprite.h>
#include "CoreRect.h"
#include "CoreTexture.h"

class CoreBody : public CoreRect
{
	BOOL Initialized;
	float _RotationRadian;
	hgeSprite* lpSprite;

	public:
	const float& RotationRadian;

	CoreBody();
	CoreBody(const CoreVector& Center, const CoreTexture& Texture);
	void Initialize(const CoreVector& Center, const CoreTexture& Texture);
	virtual ~CoreBody();

	virtual void RotationSet(float RotationRadian);
	virtual void RotationOffset(float OffsetRadian);
	virtual void Move(const CoreVector& Center);
	virtual void Render();
};

