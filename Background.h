#pragma once
#include <hge.h>
#include <hgesprite.h>

#define BackgroundCount 5

class Background
{
	HTEXTURE hTexture[BackgroundCount];
	hgeSprite* lpSprite[BackgroundCount];
	int Index;
	int TickLastToggle;

	public:
	Background();
	~Background();
	void Toggle();
	void Render(float Width, float Height);

	private:
	hgeSprite* LoadAsSprite(HTEXTURE hTexture);
};
