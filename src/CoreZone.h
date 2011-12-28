#pragma once
#include "CoreRect.h"
#include "CoreBodyList.h"
#include "CoreBackground.h"

class CoreZone : public CoreRect, public CoreBodyList
{
	CoreRect ScreenRect; //The screen rectangle within the zone
	CoreRect NoScrollRect; //The rectangle within ScreenRect where no scrolling occurs
	CoreVector ZoneToScr; //Used to convert zone coordinates to screen coordinates
	CoreVector RenderOffset; //The Offset CoreVector used to render to the screen

	CoreBackground* lpCoreBG; //To draw the background tiles

	//The ScreenRect is moved to display this body within NoScrollRect
	CoreBody* lpTrackBody; //Camera Focus

	public:
	CoreZone(const CoreVector& ZoneSize);
	virtual ~CoreZone();
	void TrackBody(CoreBody& lpBody);
	void ToggleBG();

	private:
	void UpdateScreenRect();
	void ClipToZone() const;
	void DoStuff() const;

	public:
	void Update(float Delta);
	void Render() const;
};
