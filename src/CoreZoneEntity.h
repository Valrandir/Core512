#pragma once
class CoreVector;

class CoreZoneEntity
{
	public:
	virtual void Render(const CoreVector& ZoneGridPos, const CoreVector& Offset) const = 0;
	virtual ~CoreZoneEntity();
};
