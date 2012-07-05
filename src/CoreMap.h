#pragma once
#include "CoreVecInt.h"
class CoreZoneEntity;

class CoreMap
{
	unsigned int ByteSize;
	CoreVecInt MapSize;
	CoreZoneEntity** Map;

	public:
	typedef BOOL (*MapCallbackFunc)(const CoreVecInt& MapPosition, CoreZoneEntity* Entity, const void* const Param);
	CoreMap(const CoreVecInt& Size);
	CoreMap(const CoreVecInt& PixelSize, const CoreVecInt& SquareSize);
	~CoreMap();

	private:
	void Initialize(const CoreVecInt& Size);
	void FixArea(CoreVecInt& TopLeft, CoreVecInt& Size);

	public:
	const CoreVecInt& GetMapSize() const;

	//Set each Map square in the specified range to Entity
	void SetArea(CoreVecInt TopLeft, CoreVecInt Size, CoreZoneEntity* Entity);

	//For each Map square in the specified range containing an Entity, call MapCallbackFunc
	void Scanner(CoreVecInt TopLeft, CoreVecInt Size, MapCallbackFunc Callback, const void* const Param);
};
