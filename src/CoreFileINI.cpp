#include <stdlib.h>
#include <tchar.h>
#include "CoreErrExit.h"
#include "CoreFileINI.h"

namespace
{
	const int BufferSize = 256;
	TCHAR Buffer[BufferSize * sizeof(TCHAR)];
}

CoreFileINI::CoreFileINI(LPCTSTR IniFileName)
{
	Stackit;
	TCHAR* ptr;
	Try(GetModuleFileName(GetModuleHandle(NULL), FileINI, MAX_PATH));
	for(ptr = FileINI + _tcslen(FileINI) - 1; ptr != FileINI, *ptr != '\\'; --ptr);
	_tcscpy_s(ptr + 1, _tcslen(IniFileName) + 1, IniFileName);
}

int CoreFileINI::GetInt(LPCTSTR Section, LPCTSTR Key, int Default)
{
	Stackit;
	DWORD Ret;
	Try(Ret = GetPrivateProfileString(Section, Key, NULL, Buffer, BufferSize, FileINI));
	if(Ret)
		return _ttoi(Buffer);
	return Default;
}

float CoreFileINI::GetFloat(LPCTSTR Section, LPCTSTR Key, float Default)
{
	Stackit;
	DWORD Ret;
	Try(Ret = GetPrivateProfileString(Section, Key, NULL, Buffer, BufferSize, FileINI));
	if(Ret)
		return (float)_ttof(Buffer);
	return Default;
}

LPCTSTR CoreFileINI::GetString(LPCTSTR Section, LPCTSTR Key, LPCTSTR Default)
{
	Stackit;
	DWORD Ret;
	Try(Ret = GetPrivateProfileString(Section, Key, NULL, Buffer, BufferSize, FileINI));
	if(Ret)
		return Buffer;
	return Default;
}

DWORD CoreFileINI::GetHex(LPCTSTR Section, LPCTSTR Key, DWORD Default)
{
	Stackit;
	DWORD Ret;
	Try(Ret = GetPrivateProfileString(Section, Key, NULL, Buffer, BufferSize, FileINI));
	if(Ret)
		return (DWORD)strtoul(Buffer, NULL, 16);
	return Default;
}
