#pragma once
#include "CoreRect.h"
#include "CoreBodyList.h"
#include "CoreBackground.h"

class CoreZone : public CoreRect, public CoreBodyList
{
	//This class is for the deadzone borders
	class BorderRect : public CoreRect
	{
		public:
		DWORD Colors[4];
		BorderRect();
		void SetColors(DWORD TopLeft, DWORD TopRight, DWORD BottomRight, DWORD BottomLeft);
		BorderRect& Clone(BorderRect& Specimen) const;
	};

	CoreRect ScreenRect; //The screen rectangle within the zone
	CoreRect NoScrollRect; //The rectangle within ScreenRect where no scrolling occurs
	CoreVector ZoneToScr; //Used to convert zone coordinates to screen coordinates
	CoreVector RenderOffset; //The Offset CoreVector used to render to the screen
	BorderRect vBorderRect[8]; //One on each side and one on each corners
	CoreBackground* lpCoreBG; //To draw the background tiles

	//The ScreenRect is moved to display this body within NoScrollRect
	CoreBody* lpTrackBody; //Camera Focus

	public:
	CoreZone(const CoreVector& ZoneSize);
	virtual ~CoreZone();
	void TrackBody(CoreBody& lpBody);
	void ToggleBG();

	private:
	void InitBorders();
	void UpdateScreenRect();
	void RenderVisibleBorders() const;

	public:
	void Update(float Delta);
	void Render() const;
};
