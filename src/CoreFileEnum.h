#pragma once
#include <vector>
#include <string>

typedef std::vector<std::string*> CoreFileEnumVec;

class CoreFileEnum
{
	CoreFileEnumVec vFiles;
	void Clear();

	public:
	~CoreFileEnum();
	CoreFileEnumVec* FileList(const char* FileName, const char* Prefix);
};
