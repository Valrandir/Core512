#pragma once
#include <vector>
#include <string>

typedef std::vector<std::string*> CoreFileEnumVec;

class CoreFileEnum
{
	public:
	static int FileList(CoreFileEnumVec* vFiles, const char* FileName);
};
