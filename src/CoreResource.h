#pragma once
#include <map>
#include "CoreTexture.h"

class CoreResource
{
	typedef std::map<const char*,void*> ResMap;
	typedef std::pair<const char*,void*> ResMapPair;
	typedef ResMap::iterator ResMapIterator;

	ResMap vSilo;

	public:
	~CoreResource();
	CoreTexture* LinkTexture(const char* ResPath);

	private:
	bool Link(const char* ResPath, void*& Value);
};
