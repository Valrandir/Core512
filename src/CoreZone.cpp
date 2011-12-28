#include "CoreDefs.h"
#include "CoreZone.h"

CoreZone::CoreZone(const CoreVector& ZoneSize) : lpCoreBG(NULL), lpTrackBody(NULL)
{
	Stackit;

	//Init Zone Rect
	CoreRect::SetByCenter(ZoneSize);

	//Init ScreenRect
	CoreVector ScreenSize;
	CoreSys.GetScreenSize(ScreenSize);
	ScreenRect.SetByCenter(ScreenSize);

	//Init NoScrollRect
	NoScrollRect.SetByCenter(ScreenSize / 1.25);

	//Init CoreBackground
	Try(lpCoreBG = new CoreBackground());
}

CoreZone::~CoreZone()
{
	DeleteNull(lpCoreBG);
}

void CoreZone::TrackBody(CoreBody& lpBody)
{
	lpTrackBody = &lpBody;
	if(lpTrackBody)
		ScreenRect.Move(lpTrackBody->Center);
}

void CoreZone::ToggleBG()
{
	lpCoreBG->Toggle();
}

void CoreZone::UpdateScreenRect()
{
	CoreVector Offset;

	if(lpTrackBody)
	{
		if(NoScrollRect.PointOffset(lpTrackBody->Center, Offset))
		{
			ScreenRect.Offset(Offset);
			NoScrollRect.Offset(Offset);
		}
	}
	else
	{
		ScreenRect.Move(Center);
		NoScrollRect.Move(Center);
	}
}

void CoreZone::Update(float Delta)
{
	CoreBodyList::Update(Delta);
	UpdateScreenRect();
}

/*
void CoreZone::DoStuff() const
{
	const int DeathZoneLength = 1024;
	float y = ViewOffset.y - ZoneToScrVec.y;
	float top = xy1.y + DeathZoneLength;
	if(y < top)
	{
		y = top - y;
		float worldtop = xy1.y - ViewOffset.y + ZoneToScrVec.y;
		CoreSys.Draw->RenderRect(0, worldtop, ScreenSize.x, y, 0xFF0000FF);
		CoreSys.Draw->RenderLine(ZoneToScrVec.x, 0, ZoneToScrVec.x, y, 0xFF00FF00);
	}
}
*/

void CoreZone::Render() const
{
	lpCoreBG->RenderMosaic(ScreenRect.Center);
	//DoStuff();
	CoreBodyList::Render(ScreenRect.Size / 2 - ScreenRect.Center);
}
