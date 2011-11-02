#include "CoreErrExit.h"
#include "CoreFileINI.h"
#include "CoreConfig.h"

CoreConfig::CoreConfig()
{
	//[Core512]
	HideTexture = false;
	BackGroundColor = 0xFF000000;
	TextColor = 0xFFFFFFFF;

	//[WindowSize]
	Width = 0;
	Height = 0;
}

void CoreConfig::ReadFileINI()
{
	Stackit;
	CoreFileINI FileINI("Core512.ini");

	//[Core512]
	HideTexture = FileINI.GetInt("Core512", "HideTexture", HideTexture);
	BackGroundColor = FileINI.GetHex("Core512", "BackGroundColor", BackGroundColor);
	TextColor = FileINI.GetHex("Core512", "TextColor", TextColor);

	//[WindowSize]
	Width = FileINI.GetInt("Resolution", "Width", Width);
	Height = FileINI.GetInt("Resolution", "Height", Height);
}
