#include "CoreDefs.h"
#include "CoreZone.h"

CoreZone::CoreZone() : lpCoreBG(NULL), lpTrackBody(NULL)
{
	Stackit;
	const int WorldSizeMultiplier = 10;

	CoreSys.GetScreenSize(ScreenSize);
	CoreRect::SetByCenter(CoreVector(), ScreenSize * WorldSizeMultiplier);
	ZoneToScrVec.Set(ScreenSize / 2);
	NoScrollRect.SetByCenter(ViewOffset, ScreenSize / 1.25);

	Try(lpCoreBG = new CoreBackground());
}

CoreZone::~CoreZone()
{
	DeleteNull(lpCoreBG);
}

CoreVector CoreZone::GetViewOffset() const
{
	return ViewOffset;
}

void CoreZone::TrackBody(CoreBody& lpBody)
{
	lpTrackBody = &lpBody;
	if(lpTrackBody)
		ViewOffset = lpTrackBody->Center;
}

void CoreZone::ToggleBG()
{
	lpCoreBG->Toggle();
}

void CoreZone::Update(float Delta)
{
	CoreBodyList::Update(Delta);

	if(lpTrackBody)
	{
		CoreVector cros;

		NoScrollRect.Move(ViewOffset);
		if(NoScrollRect.PointOffset(lpTrackBody->Center, cros))
			ViewOffset += cros;
	}
	else
		ViewOffset = 0;
}

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

void CoreZone::Render() const
{
	lpCoreBG->RenderMosaic(ViewOffset);
	DoStuff();
	CoreBodyList::Render(ZoneToScrVec - ViewOffset);
}
