#include "Core512.h"
#include "Vertex.h"
#include "Background.h"

Background::Background() : Index(0), TickLastToggle(0)
{
	hTexture[0] = exResources.GetTexture("Res\\Background1.png")->hTexture;
	hTexture[1] = exResources.GetTexture("Res\\Background2.png")->hTexture;
	hTexture[2] = exResources.GetTexture("Res\\Background3.png")->hTexture;
	hTexture[3] = exResources.GetTexture("Res\\Background4.png")->hTexture;
	hTexture[4] = exResources.GetTexture("Res\\Background5.png")->hTexture;

	for(int i = 0; i < BackgroundCount; ++i)
		lpSprite[i] = LoadAsSprite(hTexture[i]);
}

Background::~Background()
{
	for(int i = 0; i < BackgroundCount; ++i)
	{
		DeleteHgeTexture(hTexture[i])
		DeleteNull(lpSprite[i]);
	}
}

void Background::Toggle()
{
	int Tick = GetTickCount();

	if(TickLastToggle)
		if(Tick - TickLastToggle < 250)
			return;

	if(++Index > BackgroundCount)
		Index = 0;

	TickLastToggle = Tick;
}

void Background::Clear() const
{
	exHGE->Gfx_Clear(exConfig.BackGroundColor);
}

void Background::Render(int ScreenWidth, int ScreenHeight) const
{
	if(!Index)
		Clear();
	else
		lpSprite[Index - 1]->RenderStretch(0.0f, 0.0f, (float)ScreenWidth, (float)ScreenHeight);
}

void Background::RenderMosaic(int ScreenWidth, int ScreenHeight, Vertex Offset) const
{
	Vertex tex, i;
	hgeSprite* spr;

	if(!Index)
	{
		Clear();
		return;
	}

	spr = lpSprite[Index - 1];
	tex.x = spr->GetWidth();
	tex.y = spr->GetHeight();

	Offset.x = float((int)Offset.x % (int)tex.x);
	Offset.y = float((int)Offset.y % (int)tex.y);
	if(Offset.x < 0) Offset.x = tex.x + Offset.x;
	if(Offset.y < 0) Offset.y = tex.y + Offset.y;

	ScreenWidth += (int)tex.x;
	ScreenHeight += (int)tex.y;

	for(i.y = 0; i.y < ScreenHeight; i.y += tex.y)
		for(i.x = 0; i.x < ScreenWidth; i.x += tex.x)
			spr->Render(i.x - Offset.x, i.y - Offset.y);
}

hgeSprite* Background::LoadAsSprite(HTEXTURE hTexture)
{
	float width, height;
	Texture::GetSize(hTexture, width, height);
	return new hgeSprite(hTexture, 0, 0, width, height);
}
