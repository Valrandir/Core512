#pragma once

#include <vector>
#include <hge.h>
#include <hgesprite.h>
#include "CoreVector.h"

class CoreBackground
{
	std::vector<hgeSprite*> vSprites;
	std::vector<hgeSprite*>::iterator vSpritesIndex;
	int TickLastToggle;
	float ScrWidth, ScrHeight;

	public:
	CoreBackground();
	~CoreBackground();
	void Toggle();
	void Clear() const;
	void Render() const;
	void RenderMosaic(const CoreVector& Offset) const;
};
