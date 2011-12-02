#include "CoreErrExit.h"
#include "CoreDefs.h"
#include "CoreBody.h"

CoreBody::CoreBody() : RotationRadian(_RotationRadian), _RotationRadian(0.0f), Initialized(FALSE)
{
}

CoreBody::CoreBody(const CoreVector& Center, const CoreTexture& Texture) : RotationRadian(_RotationRadian), _RotationRadian(0.0f), Initialized(FALSE)
{
	Stackit;
	Initialize(Center, Texture);
}

void CoreBody::Initialize(const CoreVector& Center, const CoreTexture& Texture)
{
	Stackit;
	Trn(Initialized);
	CoreVector Size(Texture.WidthF, Texture.HeightF);

	Sprite = CoreSys.CoreSpriteCreate(Texture);
	CoreRect::SetByCenter(Center, Size);

	Initialized = TRUE;
}

CoreBody::~CoreBody()
{
	DeleteNull(Sprite)
}

void CoreBody::RotationSet(float RotationRadian)
{
	Stackit;
	Try(Initialized);

	if(RotationRadian < 0)
		RotationRadian = CoreRad1 + RotationRadian;

	if(RotationRadian > CoreRad1)
		RotationRadian = RotationRadian - CoreRad1;

	if(RotationRadian < 0 || RotationRadian > CoreRad1)
		RotationRadian = 0;

	_RotationRadian = RotationRadian;
}

void CoreBody::RotationOffset(float OffsetRadian)
{
	Stackit;
	Try(Initialized);

	RotationSet(_RotationRadian + OffsetRadian);
}

void CoreBody::Move(const CoreVector& Center)
{
	Stackit;
	Try(Initialized);

	CoreRect::Move(Center);
}

void CoreBody::Update(float Delta)
{
}

void CoreBody::DrawRect(const CoreRect& Rect) const
{
	CoreSys.Hge->Gfx_RenderLine(Rect.xy1.x, Rect.xy1.y, Rect.xy2.x, Rect.xy1.y);
	CoreSys.Hge->Gfx_RenderLine(Rect.xy2.x, Rect.xy1.y, Rect.xy2.x, Rect.xy2.y);
	CoreSys.Hge->Gfx_RenderLine(Rect.xy2.x, Rect.xy2.y, Rect.xy1.x, Rect.xy2.y);
	CoreSys.Hge->Gfx_RenderLine(Rect.xy1.x, Rect.xy2.y, Rect.xy1.x, Rect.xy1.y);
}

void CoreBody::Render() const
{
	Stackit;

	if(CoreSys.Config->DrawRect)
		DrawRect(*this);

	Render(CoreVector());
}

void CoreBody::Render(const CoreVector& Offset) const
{
	Stackit;
	Try(Initialized);

	if(CoreSys.Config->DrawRect)
	{
		CoreRect Rect = (*this);
		Rect.Offset(Offset);
		DrawRect(Rect);
	}

	if(_RotationRadian)
		Sprite->RenderEx(CoreRect::Center + Offset, _RotationRadian);
	else
		Sprite->Render(CoreRect::Center + Offset);
}

