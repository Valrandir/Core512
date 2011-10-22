#include "Core512.h"
#include "TextOut.h"

Font::Font()
{
	lpFont = new hgeFont("Res/HgeFont.fnt");
	lpFont->SetColor(0xFF000000);
}

Font::~Font()
{
	DeleteNull(lpFont);
}

void Font::Render(float x, float y, const char* Text)
{
	lpFont->Render(x, y, HGETEXT_LEFT, Text);
	//lpFont->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d (constant)", hge->Timer_GetDelta(), hge->Timer_GetFPS());
}
