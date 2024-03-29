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

void CoreBody::Render()
{
	Stackit;
	Try(Initialized);

	if(CoreSys.Config->DrawRect)
	{
		CoreSys.Hge->Gfx_RenderLine(xy1.x, xy1.y, xy2.x, xy1.y);
		CoreSys.Hge->Gfx_RenderLine(xy2.x, xy1.y, xy2.x, xy2.y);
		CoreSys.Hge->Gfx_RenderLine(xy2.x, xy2.y, xy1.x, xy2.y);
		CoreSys.Hge->Gfx_RenderLine(xy1.x, xy2.y, xy1.x, xy1.y);
	}

	if(_RotationRadian)
		Sprite->RenderEx(CoreRect::Center, _RotationRadian);
	else
		Sprite->Render(CoreRect::Center);
}
