#include "ErrExit.h"
#include "CoreDefs.h"
#include "CoreBody.h"

CoreBody::CoreBody(const CoreVector& Center, const CoreTexture& Texture) : RotationRadian(_RotationRadian), _RotationRadian(0.0f)
{
	Stackit;

	lpSprite = new hgeSprite(Texture.TextureHandle, 0.0f, 0.0f, Texture.WidthF, Texture.HeightF);
	Trn(lpSprite == NULL);
	lpSprite->SetHotSpot(Texture.WidthF / 2.0f, Texture.HeightF / 2.0f);

	CoreRect::SetByCenter(Center, CoreVector(Texture.WidthF, Texture.HeightF));
}

CoreBody::~CoreBody()
{
	DeleteNull(lpSprite)
}

void CoreBody::RotationSet(float RotationRadian)
{
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
	RotationSet(_RotationRadian + OffsetRadian);
}

void CoreBody::Move(const CoreVector& Center)
{
	CoreRect::Move(Center);
}

void CoreBody::Render()
{
	if(_RotationRadian)
		lpSprite->RenderEx(CoreRect::Center.x, CoreRect::Center.y, _RotationRadian);
	else
		lpSprite->Render(CoreRect::Center.x, CoreRect::Center.y);
}
