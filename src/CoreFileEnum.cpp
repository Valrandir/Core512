#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "CoreFileEnum.h"

int CoreFileEnum::FileList(CoreFileEnumVec* vFiles, const char* FileName, const char* Prefix)
{
	HANDLE hFind;
	WIN32_FIND_DATA FindData;
	std::string* FilePath;

	vFiles->clear();
	hFind = FindFirstFile(FileName, &FindData);

	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			FilePath = new std::string(FindData.cFileName);
			FilePath->insert(0, Prefix);
			vFiles->push_back(FilePath);
		}
		while(FindNextFile(hFind, &FindData));
		FindClose(hFind);
	}

	return vFiles->size();
}

/*
	CoreFileEnumVec vFiles;
	int s = CoreFileEnum::FileList(&vFiles, "Res/Background*.png");

	for(auto it = vFiles.begin(); it != vFiles.end(); ++it)
		MessageBox(HWND_DESKTOP, (*it)->c_str(), "", MB_OK);
*/
