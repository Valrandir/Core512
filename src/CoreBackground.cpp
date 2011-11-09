#include "CoreSystem.h"
#include "CoreFileEnum.h"
#include "CoreBackground.h"

CoreBackground::CoreBackground()
{
	CoreFileEnum FileEnum;
	CoreFileEnumVec* vFiles;
	CoreTexture* Texture;
	CoreSprite* Sprite;

	ScreenSize.x = (float)CoreSys.Config->Width;
	ScreenSize.y = (float)CoreSys.Config->Height;

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

	if(vSpritesIndex == vSprites.end())
	{
		Clear();
		return;
	}

	Sprite = *vSpritesIndex;
	tex = Sprite->GetSize();
	max = ScreenSize;

	Offset.x = float((int)Offset.x % (int)tex.x);
	Offset.y = float((int)Offset.y % (int)tex.y);
	if(Offset.x < 0) Offset.x = tex.x + Offset.x;
	if(Offset.y < 0) Offset.y = tex.y + Offset.y;
	max += tex;

	for(i.y = 0; i.y < max.y; i.y += tex.y)
		for(i.x = 0; i.x < max.x; i.x += tex.x)
			Sprite->Render(i - Offset);
}
