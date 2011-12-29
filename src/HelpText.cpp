#include "CoreDefs.h"
#include "CoreErrExit.h"
#include "HelpText.h"

HelpText::HelpText()
{
	TextStr = "Core512 is best.\n\nControls :\n";
	TextStr.append("- Thrust -> Up Arrow / Down Arrow / Mouse Buttons\n");
	TextStr.append("- Rotate -> Left Arrow / Right Arrow / D / F\n");
	TextStr.append("- Shoot -> Space\n");
	TextStr.append("- Reset Ship -> R\n");
	TextStr.append("- Toggle Background -> T\n");
	TextStr.append("- Toggle Music -> M\n");
	TextStr.append("- Explode -> X\n");
	TextStr.append("- Quit -> Escape");
}

void HelpText::Render()
{
	Text.Render(CoreVector(8, 8), TextStr.c_str());
	Text.RenderFPS(CoreVector(8, 310));
}
