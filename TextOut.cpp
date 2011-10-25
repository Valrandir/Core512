#include "Core512.h"
#include "TextOut.h"

Font::Font()
{
	lpFont = new hgeFont("Res/HgeFont.fnt");
	lpFont->SetColor(exConfig.TextColor);
}

Font::~Font()
{
	DeleteNull(lpFont);
}

void Font::Render(float x, float y, const char* Text)
{
	lpFont->Render(x, y, HGETEXT_LEFT, Text);
}

void Font::RenderFPS(float x, float y)
{
	int FPS = 1 + exHGE->Timer_GetFPS();
	lpFont->printf(x, y, HGETEXT_LEFT, "FPS : %d", FPS);
}
