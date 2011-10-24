#include "Core512.h"
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

void Background::Render(float Width, float Height)
{
	if(Index)
		lpSprite[Index - 1]->Render4V(0.0f, 0.0f, Width, 0.0f, Width, Height, 0.0f, Height);
}

hgeSprite* Background::LoadAsSprite(HTEXTURE hTexture)
{
	float width, height;
	Texture::GetSize(hTexture, width, height);
	return new hgeSprite(hTexture, 0, 0, width, height);
}
