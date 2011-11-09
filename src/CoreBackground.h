#pragma once

#include <vector>
#include "CoreVector.h"
#include "CoreSprite.h"

class CoreBackground
{
	std::vector<CoreSprite*> vSprites;
	std::vector<CoreSprite*>::iterator vSpritesIndex;
	int TickLastToggle;
	CoreVector ScreenSize;

	public:
	CoreBackground();
	~CoreBackground();
	void Toggle();
	void Clear() const;
	void Render() const;
	void RenderMosaic(const CoreVector& Offset) const;
};
