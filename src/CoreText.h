#pragma once
#include <hgefont.h>
#include "CoreVector.h"

class CoreText
{
	hgeFont* Font;

	public:
	CoreText();
	~CoreText();

	void Render(const CoreVector& Point, const char* Text) const;
	void RenderFPS(const CoreVector& Point) const;
};
