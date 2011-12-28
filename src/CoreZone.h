#pragma once
#include "CoreRect.h"
#include "CoreBodyList.h"
#include "CoreBackground.h"

class CoreZone : public CoreRect, public CoreBodyList
{
	//The screen rectangle within the zone
	CoreRect ScreenRect;

	//The rectangle within ScreenRect where no scrolling occurs
	CoreRect NoScrollRect;

	//To draw the background tiles
	CoreBackground* lpCoreBG;

	//Camera Focus
	//The ScreenRect is moved to display this body within NoScrollRect
	CoreBody* lpTrackBody;

	public:
	CoreZone(const CoreVector& ZoneSize);
	virtual ~CoreZone();
	void TrackBody(CoreBody& lpBody);
	void ToggleBG();
	void UpdateScreenRect();
	void Update(float Delta);
	void DoStuff() const;
	void Render() const;
};
