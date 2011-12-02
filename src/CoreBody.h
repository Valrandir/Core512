#pragma once
#include "CoreRect.h"
#include "CoreTexture.h"
#include "CoreSprite.h"

class CoreBody : public CoreRect
{
	BOOL Initialized;
	float _RotationRadian;
	CoreSprite* Sprite;

	public:
	const float& RotationRadian;

	CoreBody();
	CoreBody(const CoreVector& Center, const CoreTexture& Texture);
	void Initialize(const CoreVector& Center, const CoreTexture& Texture);
	virtual ~CoreBody();

	virtual void RotationSet(float RotationRadian);
	virtual void RotationOffset(float OffsetRadian);
	virtual void Move(const CoreVector& Center);
	virtual void Update(float Delta);
	void DrawRect(const CoreRect& Rect) const;
	virtual void Render() const;
	virtual void Render(const CoreVector& Offset) const;
};

