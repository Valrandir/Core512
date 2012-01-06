#include "CoreDefs.h"
#include "CoreSprite.h"

CoreSprite::CoreSprite() : Sprite(NULL), Initialized(FALSE)
{
}

CoreSprite::CoreSprite(const CoreTexture& Texture, bool CenterHotSpot) : Initialized(FALSE)
{
	Stackit;
	Initialize(Texture, CenterHotSpot);
}

CoreSprite::~CoreSprite()
{
	DeleteNull(Sprite);
}

void CoreSprite::Initialize(const CoreTexture& Texture, bool CenterHotSpot)
{
	Stackit;
	Trn(Initialized);

	Sprite = new hgeSprite(Texture.TextureHandle, 0.0f, 0.0f, Texture.WidthF, Texture.HeightF);
	Try(Sprite);
	if(CenterHotSpot)
		Sprite->SetHotSpot(floor(Texture.WidthF / 2), floor(Texture.HeightF / 2));

	Initialized = TRUE;
}

CoreVector CoreSprite::GetSize() const
{
	return CoreVector(Sprite->GetWidth(), Sprite->GetHeight());
}

void CoreSprite::Render(const CoreVector& Position) const
{
	Sprite->Render(Position.x, Position.y);
}

void CoreSprite::RenderEx(const CoreVector& Position, float RotationRadian) const
{
	Sprite->RenderEx(Position.x, Position.y, RotationRadian);
}

void CoreSprite::RenderStretch(const CoreVector& Position, const CoreVector& Size) const
{
	Sprite->RenderStretch(Position.x, Position.y, Size.x, Size.y);
}

void CoreSprite::RenderRect(const CoreRect& Area)
{
	Sprite->SetTextureRect(Area.xy1.x, Area.xy1.y, Area.Size.x, Area.Size.y);
	//Sprite->Render(Area.Center.x, Area.Center.y);
}
