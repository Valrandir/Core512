#include "CoreDefs.h"
#include "CoreZone.h"

CoreZone::CoreZone() : lpCoreBG(NULL), lpTrackBody(NULL)
{
	Stackit;
	float Width = (float)CoreSys.Config->Width * 10;
	float Height = (float)CoreSys.Config->Height * 10;

	CoreRect::SetByCenter(CoreVector(), CoreVector(Width, Height));

	ZoneToScrVec.Set(CoreSys.Config->Width / 2.0f, CoreSys.Config->Height / 2.0f);

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

	//TODO Integrate this into CoreZone
	if(lpTrackBody)
	{
		CoreRect cr;
		cr.SetByCenter(ViewOffset, CoreVector(384, 384));

		CoreVector cros;
		if(cr.PointOffset(lpTrackBody->Center, cros))
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
