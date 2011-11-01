#include <stdlib.h>
#include <tchar.h>
#include "CoreFileINI.h"

namespace
{
	const int BufferSize = 256;
	TCHAR Buffer[BufferSize * sizeof(TCHAR)];
}

CoreFileINI::CoreFileINI(LPCTSTR IniFileName)
{
	TCHAR* ptr;
	GetModuleFileName(GetModuleHandle(NULL), FileINI, MAX_PATH);
	for(ptr = FileINI + _tcslen(FileINI) - 1; ptr != FileINI, *ptr != '\\'; --ptr);
	_tcscpy_s(ptr + 1, _tcslen(IniFileName) + 1, IniFileName);
}

int CoreFileINI::FileINI_GetInt(LPCTSTR Section, LPCTSTR Key, int Default)
{
	if(GetPrivateProfileString(Section, Key, NULL, Buffer, BufferSize, FileINI))
		return _ttoi(Buffer);
	return Default;
}

float CoreFileINI::FileINI_GetFloat(LPCTSTR Section, LPCTSTR Key, float Default)
{
	if(GetPrivateProfileString(Section, Key, NULL, Buffer, BufferSize, FileINI))
		return (float)_ttof(Buffer);
	return Default;
}

LPCTSTR CoreFileINI::FileINI_GetString(LPCTSTR Section, LPCTSTR Key, LPCTSTR Default)
{
	if(GetPrivateProfileString(Section, Key, NULL, Buffer, BufferSize, FileINI))
		return Buffer;
	return Default;
}

DWORD CoreFileINI::FileINI_GetHex(LPCTSTR Section, LPCTSTR Key, DWORD Default)
{
	if(GetPrivateProfileString(Section, Key, NULL, Buffer, BufferSize, FileINI))
		return (DWORD)strtoul(Buffer, NULL, 16);
	return Default;
}
