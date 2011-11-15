#include "CoreDefs.h"
#include "CoreZone.h"

CoreZone::CoreZone() : lpCoreBG(NULL)
{
	Stackit;
	float Width = (float)CoreSys.Config->Width;
	float Height = (float)CoreSys.Config->Height;

	CoreRect::SetByCenter(CoreVector(), CoreVector(Width, Height));

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

void CoreZone::ToggleBG()
{
	lpCoreBG->Toggle();
}

void CoreZone::Render(const CoreVector& Offset) const
{
	lpCoreBG->RenderMosaic(Offset);
	CoreBodyList::Render(ViewOffset);
}
