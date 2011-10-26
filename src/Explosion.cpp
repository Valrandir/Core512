#include "Core512.h"
#include "Explosion.h"

Explosion::Explosion()
{
	HTEXTURE hTexture;

	hTexture = exResources.GetTexture("Res\\Explosion.png")->hTexture;
	Texture::GetSize(hTexture, Width, Height);
	Width /= 5;
	Height /= 5;

	lpAnimation = new hgeAnimation(hTexture, 25, 50.5f, 0.0f, 0.0f, 96.0f, 96.0f);
	lpAnimation->SetMode(HGEANIM_FWD | HGEANIM_NOLOOP);
	lpAnimation->SetHotSpot(Width / 2, Height / 2);
}

Explosion::~Explosion()
{
}

void Explosion::Play()
{
	lpAnimation->Play();
}

bool Explosion::IsPlaying()
{
	return lpAnimation->IsPlaying();
}

void Explosion::Update()
{
	float Delta = exHGE->Timer_GetDelta();
	lpAnimation->Update(Delta);
}

void Explosion::Render(float x, float y) const
{
	//lpAnimation->Render(x, y);
	lpAnimation->RenderStretch(x - Width, y - Height, x + Width, y + Width);
}
