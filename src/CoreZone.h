#pragma once
#include "CoreRect.h"
#include "CoreBodyList.h"
#include "CoreBackground.h"

class CoreZone : public CoreRect, public CoreBodyList
{
	CoreVector ViewOffset;
	CoreBackground* lpCoreBG;

	public:
	CoreZone();
	virtual ~CoreZone();
	CoreVector GetViewOffset() const;
	void ToggleBG();
	void Render(const CoreVector& Offset) const;
};
