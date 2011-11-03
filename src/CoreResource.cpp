#include "CoreSystem.h"
#include "CoreResource.h"

CoreResource::~CoreResource()
{
	for(auto it = vSilo.begin(); it != vSilo.end(); ++it)
		delete it->second;
}

CoreTexture* CoreResource::LinkTexture(const char* ResPath)
{
	Stackit;

	void* Value;
	CoreTexture* lpCoreTexture;

	if(Link(ResPath, Value))
		lpCoreTexture = (CoreTexture*)Value;
	else
	{
		lpCoreTexture = CoreSys.CoreTextureCreate(ResPath);
		vSilo.insert(ResMapPair(ResPath, (void*)lpCoreTexture));
	}

	return lpCoreTexture;
}

bool CoreResource::Link(const char* ResPath, void*& Value)
{
	ResMapIterator it;

	it = vSilo.find(ResPath);
	if(it == vSilo.end())
	{
		Value = NULL;
		return false;
	}

	Value = it->second;
	return true;
}
