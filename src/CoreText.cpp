#include "CoreDefs.h"
#include "CoreSystem.h"
#include "CoreErrExit.h"
#include "CoreText.h"

extern HGE* CoreGlobalHge;
extern CoreSystem* CoreGlobalSystem;

CoreText::CoreText()
{
	Stackit;
	Try(Font = new hgeFont("Res/HgeFont.fnt"));
	Font->SetColor(CoreGlobalSystem->Config->TextColor);
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
	int FPS = float(1.0f + CoreGlobalSystem->Delta());
	Font->printf(Point.x, Point.y, HGETEXT_LEFT, "FPS : %d", FPS);
}
