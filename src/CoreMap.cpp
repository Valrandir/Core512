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

void CoreMap::FixArea(CoreVecInt& TopLeft, CoreVecInt& Size)
{
	Stackit;

	if(TopLeft.x < 0)
	{
		Size.x += TopLeft.x;
		TopLeft.x = 0;
	}

	if(TopLeft.y < 0)
	{
		Size.y += TopLeft.y;
		TopLeft.y = 0;
	}

	CoreVecInt BottomRight = TopLeft + Size;

	if(BottomRight.x >= MapSize.x)
	{
		Size.x -= BottomRight.x - MapSize.x + 1;
		BottomRight.x = TopLeft.x + Size.x;
	}

	if(BottomRight.y >= MapSize.y)
	{
		Size.y -= BottomRight.y - MapSize.y + 1;
		BottomRight.y = TopLeft.y + Size.y;
	}

	//Critical Error if TopLeft is past MapSize
	if(TopLeft.x > MapSize.x || TopLeft.y > MapSize.y)
		FinalErrorM("TopLeft is past MapSize");

	//Critical Error if Size is negative
	if(Size.x < 0 || Size.y < 0)
		FinalErrorM("Size is less than zero");

	//Critical Error if BottomRight is past MapSize
	if(BottomRight.x >= MapSize.x || BottomRight.y >= MapSize.y)
		FinalErrorM("BottomRight is past MapSize");
}

const CoreVecInt& CoreMap::GetMapSize() const
{
	return MapSize;
}

void CoreMap::SetArea(CoreVecInt TopLeft, CoreVecInt Size, CoreZoneEntity*const Entity)
{
	Stackit;
	CoreZoneEntity **py, **px; //Start Address
	CoreZoneEntity **pym, **pxm; //End Address
	FixArea(TopLeft, Size);
	py = MapIndex(TopLeft.x, TopLeft.y);
	pym = py + Size.y * MapSize.x;
	for(; py <= pym; py += MapSize.x)
		for(px = py, pxm = px + Size.x; px <= pxm; ++px)
			*px = Entity;
}

void CoreMap::Scanner(CoreVecInt TopLeft, CoreVecInt Size, MapCallbackFunc Callback, const void* const Param)
{
	Stackit;
	CoreZoneEntity **py, **px; //Start Address
	CoreVecInt cur;
	FixArea(TopLeft, Size);
	py = MapIndex(TopLeft.x, TopLeft.y);
	for(cur.y = 0; cur.y < Size.y; py += MapSize.x, ++cur.y)
		for(px = py, cur.x = 0; cur.x < Size.x; ++px, ++cur.x)
			if(*px)
				if(Callback(cur + TopLeft, *px, Param))
					return;
}
