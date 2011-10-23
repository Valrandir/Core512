#include "Core512.h"
#include "Background.h"

Background::Background() : Index(0), TickLastToggle(0)
{
	hTexture[0] = lpHGE->Texture_Load("Res\\Background1.png");
	hTexture[1] = lpHGE->Texture_Load("Res\\Background2.png");
	hTexture[2] = lpHGE->Texture_Load("Res\\Background3.png");
	hTexture[3] = lpHGE->Texture_Load("Res\\Background4.png");
	hTexture[4] = lpHGE->Texture_Load("Res\\Background5.png");

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

	if(++Index >= BackgroundCount)
		Index = 0;

	TickLastToggle = Tick;
}

void Background::Render(float Width, float Height)
{
	lpSprite[Index]->Render4V(0.0f, 0.0f, Width, 0.0f, Width, Height, 0.0f, Height);
}

hgeSprite* Background::LoadAsSprite(HTEXTURE hTexture)
{
	float width = lpHGE->Texture_GetWidth(hTexture);
	float height = lpHGE->Texture_GetHeight(hTexture);
	return new hgeSprite(hTexture, 0, 0, width, height);
}
