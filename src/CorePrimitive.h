#pragma once
#include <hge.h>
#include "CoreVector.h"
#include "CoreRect.h"

class CorePrimitive
{
	HGE* Hge;

	public:
	CorePrimitive(HGE* lpHge);

	void RenderLine(const CoreVector& xy1, const CoreVector& xy2, DWORD Color = 0xFFFFFFFF);
	void RenderLine(float x1, float y1, float x2, float y2, DWORD Color = 0xFFFFFFFF);
	void RenderRect(const CoreRect& Rect, DWORD Color = 0xFFFFFFFF);
	void RenderRect(float x1, float y1, float x2, float y2, DWORD Color = 0xFFFFFFFF);
};
