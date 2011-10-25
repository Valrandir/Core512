#pragma once
#include <WinDef.h>

struct Config
{
	BOOL HideTexture;
	DWORD BackGroundColor;
	DWORD TextColor;

	int Width;
	int Height;

	Config();
	void ReadFileINI();
};
