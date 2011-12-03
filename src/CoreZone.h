#pragma once
#include "CoreRect.h"
#include "CoreBodyList.h"
#include "CoreBackground.h"

class CoreZone : public CoreRect, public CoreBodyList
{
	CoreVector ZoneToScrVec;
	CoreVector ViewOffset;
	CoreRect NoScrollRect;

	CoreBackground* lpCoreBG;
	CoreBody* lpTrackBody;

	public:
	CoreZone();
	virtual ~CoreZone();
	CoreVector GetViewOffset() const;
	void TrackBody(CoreBody& lpBody);
	void ToggleBG();
	void Update(float Delta);
	void Render() const;
};
