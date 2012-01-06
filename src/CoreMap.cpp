#include "CoreErrExit.h"
#include "CoreMap.h"

#define MapIndex(X,Y)(Map + (Y) * (MapSize.x) + (X))

CoreMap::CoreMap(const CoreVecInt& Size)
{
	Stackit;
	Initialize(Size);
}

CoreMap::CoreMap(const CoreVecInt& PixelSize, const CoreVecInt& SquareSize)
{
	Stackit;
	CoreVecInt Size;

	int Mod; //To avoid warning in release build
	Trn(Mod = PixelSize.x % SquareSize.x);
	Trn(Mod = PixelSize.y % SquareSize.y);

	Size = PixelSize / SquareSize;
	Initialize(Size);
}

CoreMap::~CoreMap()
{
	free(Map);
}

void CoreMap::Initialize(const CoreVecInt& Size)
{
	Stackit;
	MapSize = Size;
	ByteSize = MapSize.x * MapSize.y * sizeof(CoreZoneEntity*);
	Try(Map = (CoreZoneEntity**)malloc(ByteSize));
	memset(Map, 0, ByteSize);
}

const CoreVecInt& CoreMap::GetMapSize() const
{
	return MapSize;
}

void CoreMap::SetArea(const CoreVecInt& TopLeft, const CoreVecInt& Size, CoreZoneEntity*const Entity)
{
	Stackit;
	CoreZoneEntity **py, **px; //Start Address
	CoreZoneEntity **pym, **pxm; //End Address
	py = MapIndex(TopLeft.x, TopLeft.y);
	pym = py + Size.y * MapSize.x;
	for(; py <= pym; py += MapSize.x)
		for(px = py, pxm = px + Size.x; px <= pxm; ++px)
			*px = Entity;
}

void CoreMap::Scanner(const CoreVecInt& TopLeft, const CoreVecInt& Size, MapCallbackFunc Callback, const void* const Param)
{
	Stackit;
	CoreZoneEntity **py, **px; //Start Address
	CoreVecInt cur;

	py = MapIndex(TopLeft.x, TopLeft.y);
	for(cur.y = 0; cur.y < Size.y; py += MapSize.x, ++cur.y)
		for(px = py, cur.x = 0; cur.x < Size.x; ++px, ++cur.x)
			if(*px)
				if(Callback(cur + TopLeft, *px, Param))
					return;
}
