#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class CoreFileINI
{
	TCHAR FileINI[MAX_PATH * sizeof(TCHAR)];

	public:
	CoreFileINI(LPCTSTR IniFileName);
	int GetInt(LPCTSTR Section, LPCTSTR Key, int Default);
	float GetFloat(LPCTSTR Section, LPCTSTR Key, float Default);
	LPCTSTR GetString(LPCTSTR Section, LPCTSTR Key, LPCTSTR Default);
	DWORD GetHex(LPCTSTR Section, LPCTSTR Key, DWORD Default);
};
