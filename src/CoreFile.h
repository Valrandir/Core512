#pragma once
#include <string>

class CoreFile
{
	public:
	static std::string AppPath();
	static std::string AppPath(const char* FileName);
	static bool FileExist(const std::string& FileName);
	static bool FileExist(const char* FileName);
};
