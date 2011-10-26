#include "Core512.h"
#include "Texture.h"
#include "Resources.h"

Resources::~Resources()
{
	for(auto it = vMap.begin(); it != vMap.end(); ++it)
		delete it->second;
}

Texture* Resources::GetTexture(const char* ResPath)
{
	void* Value;
	Texture* lpTexture;

	if(Get(ResPath, Value))
		lpTexture = (Texture*)Value;
	else
	{
		lpTexture = new Texture();
		lpTexture->Load(ResPath);
		vMap.insert(ResMapPair(ResPath, (void*)lpTexture));
	}

	return lpTexture;
}

bool Resources::Get(const char* ResPath, void*& Value)
{
	ResMapIterator it;

	it = vMap.find(ResPath);
	if(it == vMap.end())
	{
		Value = NULL;
		return false;
	}

	Value = it->second;
	return true;
}
