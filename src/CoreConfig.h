#pragma once
#include <WinDef.h>

struct CoreConfig
{
	BOOL HideTexture;
	DWORD BackGroundColor;
	DWORD TextColor;

	int Width;
	int Height;
	BOOL DrawRect;

	CoreConfig();
	void ReadFileINI();
};
