#include "CoreErrExit.h"
#include "CoreFileINI.h"
#include "CoreConfig.h"

CoreConfig::CoreConfig()
{
	//Section: [Core512]
	HideTexture = false;
	BackGroundColor = 0xFF000000;
	TextColor = 0xFFFFFFFF;
	ShipParticle = true;
	UseMusic = true;

	//Section: [Dynamics]
	ShipEngineForce = 50;
	ZoneSize = 4096 + 2048;
	ZoneBorderSize = 2048;

	//Section: [Resolution]
	Width = 0;
	Height = 0;

	//Section: [Debug]
	DrawRect = 0;
}

void CoreConfig::ReadFileINI()
{
	Stackit;
	CoreFileINI FileINI("Core512.ini");

	//Section: [Core512]
	BackGroundColor = FileINI.GetHex("Core512", "BackGroundColor", BackGroundColor);
	TextColor = FileINI.GetHex("Core512", "TextColor", TextColor);
	ShipParticle = FileINI.GetInt("Core512", "ShipParticle", ShipParticle);
	UseMusic = FileINI.GetInt("Core512", "UseMusic", UseMusic);

	//Section: [Dynamics]
	ShipEngineForce = FileINI.GetInt("Dynamics", "ShipEngineForce", ShipEngineForce);
	ZoneSize = FileINI.GetInt("Dynamics", "ZoneSize", ZoneSize);
	ZoneBorderSize = FileINI.GetInt("Dynamics", "ZoneBorderSize", ZoneBorderSize);

	//Section: [Resolution]
	Width = FileINI.GetInt("Resolution", "Width", Width);
	Height = FileINI.GetInt("Resolution", "Height", Height);

	//Section: [Debug]
	DrawRect = FileINI.GetInt("Debug", "DrawRect", DrawRect);
}
