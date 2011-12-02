#include "CoreSystem.h"
#include "Ship.h"

Ship::Ship()
{
	Stackit;
	CoreTexture* Texture = CoreSys.Vault->LinkTexture("Res/Ship.png");
	Texture->UseOriginalSize();
	CoreRotBody::Initialize(CoreVector(), CoreVector(0.0f, -1.0f), *Texture);
	EngineForce = 25.0f;
	TurnSpeed = 10.0f;
	lpParticle[0] = new ShipParticle();
	lpParticle[1] = new ShipParticle();
}

Ship::~Ship()
{
	DeleteNull(lpParticle[0]);
	DeleteNull(lpParticle[1]);
}

void Ship::Turn(int RotateDirection, float Delta)
{
	CoreRotBody::Turn(RotateDirection * TurnSpeed * Delta);
}

void Ship::Thrust(int ForceDirection)
{
	CoreRotBody::Thrust(ForceDirection * EngineForce);
}

void Ship::UpdateParticle()
{
	CoreVector pp[2];

	pp[0].x = CoreBody::xy1.x - CoreBody::Center.x + 16;
	pp[0].y = CoreBody::xy2.y - CoreBody::Center.y - 8;
	pp[1].x = CoreBody::xy2.x - CoreBody::Center.x - 16;
	pp[1].y = CoreBody::xy2.y - CoreBody::Center.y - 8;

	pp[0].Rotate(RotationRadian);
	pp[1].Rotate(RotationRadian);

	pp[0] += CoreBody::Center;
	pp[1] += CoreBody::Center;

	lpParticle[0]->Update(pp[0], RotationRadian + CoreRad4 + CoreRad16);
	lpParticle[1]->Update(pp[1], RotationRadian + CoreRad4 - CoreRad16);
}

void Ship::Update(float Delta)
{
	CoreRotBody::Update(Delta);
	UpdateParticle();
}

void Ship::CenterScreen()
{
	CoreBody::Move(CoreVector());
	CoreDynBody::HardStop();
}

void Ship::Render() const
{
	Stackit;
	CoreBody::Render();
	lpParticle[0]->Render();
	lpParticle[1]->Render();
}

void Ship::Render(const CoreVector& Offset) const
{
	Stackit;
	CoreBody::Render(Offset);
	lpParticle[0]->Render(Offset);
	lpParticle[1]->Render(Offset);
}
