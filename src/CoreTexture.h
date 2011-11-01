#pragma once
#include <hgesprite.h>

class CoreTexture
{
	HTEXTURE hTexture;
	int w, h;
	float wf, hf;

	public:
	const int &Width, &Height;
	const float &WidthF, &HeightF;
	const HTEXTURE& TextureHandle;

	CoreTexture(const char* ResPath);
	~CoreTexture();
};

