#include "CoreDefs.h"
#include "Asteroid.h"

Asteroid::Asteroid(CoreVecInt const & ZoneMapPos, CoreVecInt const & SquareSize) : ZoneMapPos(ZoneMapPos), SquareSize(SquareSize)
{
	Stackit;
	CoreTexture* Texture;

	//Load Texture and create Sprite
	Texture = CoreSys.Vault->LinkTexture("Res/Asteroid.png");
	Texture->UseOriginalSize();
	Sprite = CoreSys.CreateCoreSprite(*Texture);

	//Test Texture Size for power of two.
	int Mod; //To avoid warning in release build
	Trn(Mod = Texture->Width % SquareSize.x);
	Trn(Mod = Texture->Height % SquareSize.y);

	//Set SquareCount
	SquareCount.Set(Texture->Width / SquareSize.x, Texture->Height / SquareSize.y);

	//Paint the CoreZone CoreMap
	CoreSys.ActiveZoneGet()->MapSet(ZoneMapPos, SquareCount, this);
}

Asteroid::~Asteroid()
{
	delete Sprite;
}

void Asteroid::Render(const CoreVecInt& ZoneGridPos, const CoreVecInt& Offset) const
{
	//Translate from ZoneGrid to AsteroidGrid
	CoreVector Position = ZoneGridPos - this->ZoneMapPos;

	//Translate from Square to Pixels
	Position *= SquareSize;

	//Set texture coordinates to for this square
	Sprite->TextureRectSet(Position, SquareSize);

	//Render this single square
	Sprite->Render(Position + this->ZoneMapPos * SquareSize + Offset);
}
