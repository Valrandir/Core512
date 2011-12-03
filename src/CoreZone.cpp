#include "CoreDefs.h"
#include "CoreZone.h"

CoreZone::CoreZone() : lpCoreBG(NULL), lpTrackBody(NULL)
{
	Stackit;
	CoreVector ScrSize((float)CoreSys.Config->Width, (float)CoreSys.Config->Height);

	CoreRect::SetByCenter(CoreVector(), ScrSize * 10);

	ZoneToScrVec.Set(ScrSize / 2);
	NoScrollRect.SetByCenter(ViewOffset, ScrSize / 1.25);

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

void CoreZone::Render() const
{
	lpCoreBG->RenderMosaic(ViewOffset);
	CoreBodyList::Render(ZoneToScrVec - ViewOffset);
}
