#pragma once
#include <WinDef.h>

struct CoreConfig
{
	//Section: [Core512]
	BOOL HideTexture;
	DWORD BackGroundColor;
	DWORD TextColor;
	BOOL ShipParticle;
	BOOL UseMusic;

	//Section: [Dynamics]
	int ShipEngineForce;
	int ZoneSize;
	int ZoneBorderSize;

	//Section: [Resolution]
	int Width;
	int Height;

	//Section: [Debug]
	BOOL DrawRect;

	CoreConfig();
	void ReadFileINI();
};
