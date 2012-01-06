#pragma once
class CoreVector;

class CoreZoneEntity
{
	public:
	virtual void Render(CoreVector ZoneGridPos) const = 0;
	virtual ~CoreZoneEntity();
};
