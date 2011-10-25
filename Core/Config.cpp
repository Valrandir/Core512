#include "../FileINI.h"
#include "Config.h"

Config::Config()
{
	//[Core512]
	HideTexture = false;
	BackGroundColor = 0xFF000000;
	TextColor = 0xFFFFFFFF;

	//[WindowSize]
	Width = 0;
	Height = 0;
}

void Config::ReadFileINI()
{
	//[Core512]
	HideTexture = FileINI_GetInt("Core512", "HideTexture", HideTexture);
	BackGroundColor = FileINI_GetHex("Core512", "BackGroundColor", BackGroundColor);
	TextColor = FileINI_GetHex("Core512", "TextColor", TextColor);

	//[WindowSize]
	Width = FileINI_GetInt("Resolution", "Width", Width);
	Height = FileINI_GetInt("Resolution", "Height", Height);
}
