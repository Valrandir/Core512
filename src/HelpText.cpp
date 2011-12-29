#include "CoreDefs.h"
#include "CoreErrExit.h"
#include "HelpText.h"

HelpText::HelpText() :
	HelpTextContent("Core512 is best.\n\nControls :\n- Thrust -> Up Arrow / Down Arrow / Mouse Buttons\n- Rotate -> Left Arrow / Right Arrow / D / F\n- Reset Ship -> Space\n- Toggle Background -> T\n- Toggle Music -> M\n- Explode -> X\n- Quit -> Escape")
{}

void HelpText::Render()
{
	Text.Render(CoreVector(8, 8), HelpTextContent);
	Text.RenderFPS(CoreVector(8, 280));
}
