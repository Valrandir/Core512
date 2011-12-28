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

	//Init ZoneToScr
	ZoneToScr = ScreenRect.Size / 2;

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

	RenderOffset = ZoneToScr - ScreenRect.Center;
}

//Set Clipping if the outside of the zone is on screen
void CoreZone::ClipToZone() const
{
	CoreRect Mix;
	if(Intersect(ScreenRect, Mix) && ScreenRect.Size != Mix.Size)
	{
		CoreSys.ClearScreen(0xFF808080);
		Mix.Offset(RenderOffset);
		CoreSys.Clip(Mix);
	}
	else
		CoreSys.ClipReset();
}

void CoreZone::DoStuff() const
{
	CoreRect TopCenter;
	CoreRect Mix;

	//TopCenter Test
	TopCenter.SetByPoints(xy1, CoreVector(xy2.x, xy1.y + 512));
	if(ScreenRect.Intersect(TopCenter))
	{
		TopCenter.Offset(RenderOffset);
		CoreSys.Draw->RenderRect(TopCenter);
	}
}

void CoreZone::Update(float Delta)
{
	CoreBodyList::Update(Delta);
	UpdateScreenRect();
}

void CoreZone::Render() const
{
	ClipToZone();
	lpCoreBG->RenderMosaic(ScreenRect.Center);
	DoStuff();
	CoreBodyList::Render(RenderOffset);
}
