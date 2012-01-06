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

void Asteroid::Render(CoreVector ZoneGridPos) const
{
	CoreRect Area;

	//Translate from ZoneGrid to AsteroidGrid
	ZoneGridPos -= this->ZoneGridPos;

	//Translate from Square to Pixels
	ZoneGridPos *= 16.f;

	Area.SetByPoints(ZoneGridPos, ZoneGridPos + 16.f);
	Sprite->RenderRect(Area);

	ZoneGridPos += this->ZoneGridPos;
	Area.SetByPoints(ZoneGridPos, ZoneGridPos + 16.f);

	Sprite->Render(Area.Center);
}
