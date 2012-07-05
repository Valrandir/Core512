#pragma once

#include <vector>
#include "CoreVector.h"
#include "CoreSprite.h"
#include "CoreTimer.h"

class CoreBackground
{
	std::vector<CoreSprite*> vSprites;
	std::vector<CoreSprite*>::iterator vSpritesIndex;
	CoreVector ScreenSize;
	CoreTimer Timer;

	public:
	CoreBackground();
	~CoreBackground();
	void Toggle(bool Immediate = false);
	void Clear() const;
	void Render() const;
	void RenderMosaic(const CoreVector& Offset) const;
};
