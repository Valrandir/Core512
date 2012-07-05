#include "CoreDefs.h"
#include "Asteroid.h"

Asteroid::Asteroid(CoreVecInt const & ZoneMapPos, CoreVecInt const & SquareSize) : CoreZoneEntity(ZoneMapPos, SquareSize)
{
	Stackit;
	CoreTexture* Texture;

	//Load Texture and create Sprite
	Texture = CoreSys.Vault->LinkTexture("Res/Asteroid.png");
	Texture->UseOriginalSize();
	Sprite = CoreSys.CreateCoreSprite(*Texture, false);

	//Test Texture Size for power of two.
	int Mod; //To avoid warning in release build
	Trn(Mod = Texture->Width % SquareSize.x);
	Trn(Mod = Texture->Height % SquareSize.y);

	//Set SquareCount
	int x = Texture->Width / SquareSize.x;
	int y = Texture->Height / SquareSize.y;
	SquareCount.Set(x, y);

	CoreZoneEntity::ZoneMapPos.x -= x / 2;
	CoreZoneEntity::ZoneMapPos.y -= y / 2;

	//Paint the CoreZone CoreMap
	CoreSys.ActiveZoneGet()->MapSet(CoreZoneEntity::ZoneMapPos, SquareCount, this);
}

Asteroid::~Asteroid()
{
	delete Sprite;
}

void Asteroid::Render(const CoreVecInt& ZoneGridPos, const CoreVecInt& Offset) const
{
	//Render common CoreZoneEntity stuff
	CoreZoneEntity::Render(ZoneGridPos, Offset);
}
