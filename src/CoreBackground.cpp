#include "CoreSystem.h"
#include "CoreFileEnum.h"
#include "CoreBackground.h"

CoreBackground::CoreBackground()
{
	CoreFileEnumVec vFiles;
	CoreTexture* Texture;
	hgeSprite* spr;

	ScrWidth = (float)CoreSys.Config->Width;
	ScrHeight = (float)CoreSys.Config->Height;

	CoreFileEnum::FileList(&vFiles, "Res/Background*.png", "Res/");

	for(auto it = vFiles.begin(); it != vFiles.end(); ++it)
	{
		Texture = CoreSys.Vault->LinkTexture((**it).c_str());
		spr = new hgeSprite(Texture->TextureHandle, 0, 0, Texture->WidthF, Texture->HeightF);
		vSprites.push_back(spr);
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
	CoreSys.Hge->Gfx_Clear(CoreSys.Config->BackGroundColor);
}

void CoreBackground::Render() const
{
	if(vSpritesIndex == vSprites.end())
		Clear();
	else
	{
		(**vSpritesIndex).RenderStretch(0.0f, 0.0f, ScrWidth, ScrHeight);
	}
}

void CoreBackground::RenderMosaic(const CoreVector& Offset) const
{
	CoreVector tex, max, i;
	hgeSprite* spr;

	if(vSpritesIndex == vSprites.end())
	{
		Clear();
		return;
	}

	spr = *vSpritesIndex;
	tex.x = spr->GetWidth();
	tex.y = spr->GetHeight();
	max.x = ScrWidth;
	max.y = ScrHeight;

	Offset.x = float((int)Offset.x % (int)tex.x);
	Offset.y = float((int)Offset.y % (int)tex.y);
	if(Offset.x < 0) Offset.x = tex.x + Offset.x;
	if(Offset.y < 0) Offset.y = tex.y + Offset.y;
	max += tex;

	for(i.y = 0; i.y < max.y; i.y += tex.y)
		for(i.x = 0; i.x < max.x; i.x += tex.x)
			spr->Render(i.x - Offset.x, i.y - Offset.y);
}
