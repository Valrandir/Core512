#pragma once
class CoreVecInt;

class CoreZoneEntity
{
	public:
	virtual void Render(const CoreVecInt& ZoneGridPos, const CoreVecInt& Offset) const = 0;
	virtual ~CoreZoneEntity();
};
