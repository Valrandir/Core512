#pragma once
#include <hgefont.h>

struct Font
{
	hgeFont* lpFont;

	Font();
	~Font();

	void Render(float x, float y, const char* Text);
};
