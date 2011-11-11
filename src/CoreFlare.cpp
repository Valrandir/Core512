#include "CoreDefs.h"
#include "CoreFlare.h"

CoreFlare::CoreFlare() : Initialized(FALSE)
{
}

CoreFlare::CoreFlare(const CoreVector& Position, const char* ResPath, int SpritePerX, int SpritePerY) : Initialized(FALSE)
{
	Stackit;
	Initialize(Position, ResPath, SpritePerX, SpritePerY);
}

void CoreFlare::Initialize(const CoreVector& Position, const char* ResPath, int SpritePerX, int SpritePerY)
{
	Stackit;
	Trn(Initialized);
	CoreTexture* Texture;
	int nFrames;
	float w, h;
	float fps;

	this->Position = Position;

	Texture = CoreSys.Vault->LinkTexture(ResPath);

	nFrames = SpritePerX * SpritePerY;
	w = float(Texture->Width / SpritePerX);
	h = float(Texture->Height / SpritePerY);
	fps = 50.5f;

	lpAnimation = new hgeAnimation(Texture->TextureHandle, nFrames, fps, 0.0f, 0.0f, w, h);
	Trn(lpAnimation == NULL);
	lpAnimation->SetMode(HGEANIM_FWD | HGEANIM_NOLOOP);
	lpAnimation->SetHotSpot(Texture->WidthF / 2 / SpritePerX, Texture->HeightF / 2 / SpritePerY);

	Initialized = TRUE;
}

CoreFlare::~CoreFlare()
{
}

void CoreFlare::Play()
{
	Stackit;
	Try(Initialized);

	lpAnimation->Play();
}

bool CoreFlare::IsPlaying() const
{
	Stackit;
	Try(Initialized);

	return lpAnimation->IsPlaying();
}

void CoreFlare::Update(float Delta)
{
	Stackit;
	Try(Initialized);

	lpAnimation->Update(Delta);
}

void CoreFlare::Render() const
{
	Stackit;
	Try(Initialized);

	if(IsPlaying())
		lpAnimation->Render(Position.x, Position.y);
	//lpAnimation->RenderStretch(x - Width, y - Height, x + Width, y + Width);
}

