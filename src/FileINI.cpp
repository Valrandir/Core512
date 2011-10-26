#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <tchar.h>

LPCTSTR INI_FILE_NAME = TEXT("Core512.ini");
TCHAR FileINI[MAX_PATH * sizeof(TCHAR)];
TCHAR Buffer[256 * sizeof(TCHAR)];

void InitFileINI()
{
	TCHAR* ptr;
	static bool Initialized = false;

	if(!Initialized)
	{
		GetModuleFileName(GetModuleHandle(NULL), FileINI, sizeof(FileINI));
		for(ptr = FileINI + _tcslen(FileINI) - 1; ptr != FileINI, *ptr != '\\'; --ptr);
		_tcscpy_s(ptr + 1, _tcslen(INI_FILE_NAME) + 1, INI_FILE_NAME);
		Initialized = true;
	}
}

int FileINI_GetInt(LPCTSTR Section, LPCTSTR Key, int Default)
{
	InitFileINI();
	if(GetPrivateProfileString(Section, Key, NULL, Buffer, sizeof(Buffer), FileINI))
		return _ttoi(Buffer);
	return Default;
}

float FileINI_GetFloat(LPCTSTR Section, LPCTSTR Key, float Default)
{
	InitFileINI();
	if(GetPrivateProfileString(Section, Key, NULL, Buffer, sizeof(Buffer), FileINI))
		return (float)_ttof(Buffer);
	return Default;
}

LPCTSTR FileINI_GetString(LPCTSTR Section, LPCTSTR Key, LPCTSTR Default)
{
	InitFileINI();
	if(GetPrivateProfileString(Section, Key, NULL, Buffer, sizeof(Buffer), FileINI))
		return Buffer;
	return Default;
}

DWORD FileINI_GetHex(LPCTSTR Section, LPCTSTR Key, DWORD Default)
{
	InitFileINI();
	if(GetPrivateProfileString(Section, Key, NULL, Buffer, sizeof(Buffer), FileINI))
		return (DWORD)strtoul(Buffer, NULL, 16);
	return Default;
}
