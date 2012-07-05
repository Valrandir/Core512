#include "CoreDefs.h"
#include "CoreZoneEntity.h"

CoreZoneEntity::CoreZoneEntity(CoreVecInt const & ZoneMapPos, CoreVecInt const & SquareSize) : ZoneMapPos(ZoneMapPos), SquareSize(SquareSize)
{
}

CoreZoneEntity::~CoreZoneEntity()
{
}

void CoreZoneEntity::Render(const CoreVecInt& ZoneGridPos, const CoreVecInt& Offset) const
{
	//Translate from ZoneGrid to AsteroidGrid
	CoreVector Position = ZoneGridPos - this->ZoneMapPos;

	//Translate from Square to Pixels
	Position *= SquareSize;

	//Set texture coordinates to for this square
	Sprite->TextureRectSet(Position, SquareSize);

	//Offset Position
	Position = ZoneGridPos * SquareSize - Offset;

	//Render this single square
	Sprite->Render(Position);

	//Render debug gridlines
	//RenderEntityGrid(Position);

	//CoreSys.Hge->System_Log("ZoneGridPos x = %d y = %d    Offset x = %d y = %d", ZoneGridPos.x, ZoneGridPos.y, Offset.x, Offset.y);
}

//Render debug gridlines
void CoreZoneEntity::RenderEntityGrid(const CoreVector& Position) const
{
	CoreRect Rect;
	Rect.SetByCenter(Position, SquareSize);
	CoreSys.Draw->RenderRect(Rect, CoreSys.Hge->Random_Int(0, 4000000000));
}
