#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "CoreFileEnum.h"

void CoreFileEnum::Clear()
{
	for(auto it = vFiles.begin(); it != vFiles.end(); ++it)
		delete *it;
	vFiles.clear();
}

CoreFileEnum::~CoreFileEnum()
{
	Clear();
}

CoreFileEnumVec* CoreFileEnum::FileList(const char* FileName, const char* Prefix)
{
	HANDLE hFind;
	WIN32_FIND_DATA FindData;
	std::string* FilePath;

	Clear();
	hFind = FindFirstFile(FileName, &FindData);

	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			FilePath = new std::string(FindData.cFileName);
			FilePath->insert(0, Prefix);
			vFiles.push_back(FilePath);
		}
		while(FindNextFile(hFind, &FindData));
		FindClose(hFind);
	}

	return &vFiles;
}
