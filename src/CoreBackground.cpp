#include "CoreSystem.h"
#include "CoreFileEnum.h"
#include "CoreBackground.h"

CoreBackground::CoreBackground() : TickLastToggle(0)
{
	CoreFileEnum FileEnum;
	CoreFileEnumVec* vFiles;
	CoreTexture* Texture;
	CoreSprite* Sprite;

	CoreSys.GetScreenSize(ScreenSize);

	vFiles = FileEnum.FileList("Res/Background*.png", "Res/");

	for(auto it = vFiles->begin(); it != vFiles->end(); ++it)
	{
		Texture = CoreSys.Vault->LinkTexture((**it).c_str());
		Sprite = CoreSys.CoreSpriteCreate(*Texture, false);
		vSprites.push_back(Sprite);
	}

	vSpritesIndex = vSprites.end();
}

CoreBackground::~CoreBackground()
{
	for(auto it = vSprites.begin(); it != vSprites.end(); ++it)
		delete *it;
	vSprites.clear();
}

void CoreBackground::Toggle()
{
	int Tick = GetTickCount();

	if(TickLastToggle)
		if(Tick - TickLastToggle < 125)
			return;

	TickLastToggle = Tick;

	if(vSpritesIndex == vSprites.end())
		vSpritesIndex = vSprites.begin();
	else
		++vSpritesIndex;
}

void CoreBackground::Clear() const
{
	CoreSys.ClearScreen();
}

void CoreBackground::Render() const
{
	if(vSpritesIndex == vSprites.end())
		Clear();
	else
	{
		(**vSpritesIndex).RenderStretch(CoreVector(), ScreenSize);
	}
}

void CoreBackground::RenderMosaic(const CoreVector& Offset) const
{
	CoreVector tex, max, i;
	CoreSprite* Sprite;
	CoreVector TileOffset = Offset;

	if(vSpritesIndex == vSprites.end())
	{
		Clear();
		return;
	}

	Sprite = *vSpritesIndex;
	tex = Sprite->GetSize();
	max = ScreenSize;

	TileOffset.x = float((int)TileOffset.x % (int)tex.x);
	TileOffset.y = float((int)TileOffset.y % (int)tex.y);
	if(TileOffset.x < 0) TileOffset.x = tex.x + TileOffset.x;
	if(TileOffset.y < 0) TileOffset.y = tex.y + TileOffset.y;
	max += tex;

	for(i.y = 0; i.y < max.y; i.y += tex.y)
		for(i.x = 0; i.x < max.x; i.x += tex.x)
			Sprite->Render(i - TileOffset);
}
