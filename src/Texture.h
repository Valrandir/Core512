#pragma once
#include <hge.h>

struct Texture
{
	HTEXTURE hTexture;
	int Width;
	int Height;

	public:
	Texture();
	~Texture();

	HTEXTURE Load(const char* FileName);
	void GetSize(float& Width, float& Height, bool Original = false);
	static void GetSize(HTEXTURE hTexture, float& Width, float& Height, bool Original = false);
};
