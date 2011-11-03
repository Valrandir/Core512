#include "CoreDefs.h"
#include "CoreSystem.h"
#include "CoreErrExit.h"
#include "CoreText.h"

CoreText::CoreText()
{
	Stackit;
	Try(Font = new hgeFont("Res/HgeFont.fnt"));
	Font->SetColor(CoreSys.Config->TextColor);
}

CoreText::~CoreText()
{
	DeleteNull(Font);
}

void CoreText::Render(const CoreVector& Point, const char* Text) const
{
	Font->Render(Point.x, Point.y, HGETEXT_LEFT, Text);
}

void CoreText::RenderFPS(const CoreVector& Point) const
{
	int FPS = 1 + CoreSys.Hge->Timer_GetFPS();
	Font->printf(Point.x, Point.y, HGETEXT_LEFT, "FPS : %d", FPS);
}
