#pragma once
#include <hgesprite.h>

class CoreTexture;
class CoreVector;

class CoreSprite
{
	BOOL Initialized;
	hgeSprite* Sprite;

	friend class ShipParticle;

	public:
	CoreSprite();
	CoreSprite(const CoreTexture& Texture, bool CenterHotSpot = true);
	~CoreSprite();
	void Initialize(const CoreTexture& Texture, bool CenterHotSpot = true);
	CoreVector GetSize() const;
	void Render(const CoreVector& Position) const;
	void RenderEx(const CoreVector& Position, float RotationRadian) const;
	void RenderStretch(const CoreVector& Position, const CoreVector& Size);
};
