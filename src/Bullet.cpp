#include "Bullet.h"

Bullet::Bullet(const CoreVector& Center, const CoreVector& Direction)
{
	Stackit;
	CoreTexture* Texture = CoreSys.Vault->LinkTexture("Res/Bullet.png");
	Texture->UseOriginalSize();
	CoreRotBody::Initialize(Center, Direction, *Texture);
}

Bullet::~Bullet()
{
}

void Bullet::Update(float Delta)
{
	CoreRotBody::Thrust(50);
	CoreRotBody::Update(Delta);
}
