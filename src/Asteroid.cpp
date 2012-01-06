#include "CoreDefs.h"
#include "Asteroid.h"

Asteroid::Asteroid(CoreVector const & ZoneGridTopLeft)
{
	Stackit;
	CoreTexture* Texture;

	Texture = CoreSys.Vault->LinkTexture("Res/Asteroid.png");
	Texture->UseOriginalSize();
	Sprite = CoreSys.CreateCoreSprite(*Texture);

	ZoneGridPos = ZoneGridTopLeft;

	CoreVector Size(Texture->Width / 16.f, Texture->Height / 16.f);
	CoreSys.ActiveZoneGet()->GridMapSet(ZoneGridPos, Size, this);
}

Asteroid::~Asteroid()
{
	delete Sprite;
}

void Asteroid::Render() const
{
	Sprite->Render(CoreVector(0, 0));
}

void Asteroid::Render(const CoreVector& ZoneGridPos, const CoreVector& Offset) const
{
	//Translate from ZoneGrid to AsteroidGrid
	CoreVector Position = ZoneGridPos - this->ZoneGridPos;

	//Translate from Square to Pixels
	Position *= 16.f;

	Sprite->TextureRectSet(Position, CoreVector(16.f, 16.f));
	Sprite->Render(Position + this->ZoneGridPos * 16.f + Offset);
}
