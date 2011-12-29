#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>
#include "CoreErrExit.h"
#include "CoreFile.h"

std::string CoreFile::AppPath()
{
	Stackit;
	TCHAR Buffer[MAX_PATH * sizeof(TCHAR)], *ptr;
	Try(GetModuleFileName(GetModuleHandle(NULL), Buffer, MAX_PATH));
	for(ptr = Buffer + _tcslen(Buffer) - 1; ptr != Buffer, *ptr != '\\'; *ptr-- = 0);
	return Buffer;
}

std::string CoreFile::AppPath(const char* FileName)
{
	return AppPath().append(FileName);
}

bool CoreFile::FileExist(const std::string& FileName)
{
	return FileExist(FileName.c_str());
}

bool CoreFile::FileExist(const char* FileName)
{
	return  INVALID_FILE_ATTRIBUTES != GetFileAttributes(FileName);
}
