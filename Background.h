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
	void Clear() const;
	void Render(int ScreenWidth, int ScreenHeight) const;
	void RenderMosaic(int ScreenWidth, int ScreenHeight) const;

	private:
	hgeSprite* LoadAsSprite(HTEXTURE hTexture);
};
