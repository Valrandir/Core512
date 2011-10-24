#pragma once
#include <map>
#include "Texture.h"

class Resources
{
	typedef std::map<const char*,void*> ResMap;
	typedef std::pair<const char*,void*> ResMapPair;
	typedef ResMap::iterator ResMapIterator;

	ResMap vMap;

	public:
	~Resources();
	Texture* GetTexture(const char* ResPath);

	private:
	bool Get(const char* ResPath, void*& Value);
};
