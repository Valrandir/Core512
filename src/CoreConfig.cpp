#include "CoreErrExit.h"
#include "CoreFileINI.h"
#include "CoreConfig.h"

CoreConfig::CoreConfig()
{
	//[Core512]
	HideTexture = false;
	BackGroundColor = 0xFF000000;
	TextColor = 0xFFFFFFFF;
	ShipParticle = true;

	//[Resolution]
	Width = 0;
	Height = 0;

	//[Debug]
	DrawRect = 0;
}

void CoreConfig::ReadFileINI()
{
	Stackit;
	CoreFileINI FileINI("Core512.ini");

	//[Core512]
	BackGroundColor = FileINI.GetHex("Core512", "BackGroundColor", BackGroundColor);
	TextColor = FileINI.GetHex("Core512", "TextColor", TextColor);
	ShipParticle = FileINI.GetInt("Core512", "ShipParticle", ShipParticle);

	//[Resolution]
	Width = FileINI.GetInt("Resolution", "Width", Width);
	Height = FileINI.GetInt("Resolution", "Height", Height);

	//[Debug]
	DrawRect = FileINI.GetInt("Debug", "DrawRect", DrawRect);
}
