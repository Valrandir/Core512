#include "Core512.h"
#include "Texture.h"

Texture::Texture() : hTexture(NULL) {}

Texture::~Texture()
{
	if(hTexture)
		exHGE->Texture_Free(hTexture);
}

HTEXTURE Texture::Load(const char* FileName)
{
	hTexture = exHGE->Texture_Load(FileName);
	Width = exHGE->Texture_GetWidth(hTexture);
	Height = exHGE->Texture_GetWidth(hTexture);
	return hTexture;
}

void Texture::GetSize(float& Width, float& Height, bool Original)
{
	GetSize(hTexture, Width, Height, Original);
}

void Texture::GetSize(HTEXTURE hTexture, float& Width, float& Height, bool Original)
{
	Width = (float)exHGE->Texture_GetWidth(hTexture, Original);
	Height = (float)exHGE->Texture_GetHeight(hTexture, Original);
}
