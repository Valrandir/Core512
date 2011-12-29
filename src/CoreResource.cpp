#include "CoreSystem.h"
#include "CoreResource.h"

CoreResource::~CoreResource()
{
	for(auto it = vSilo.begin(); it != vSilo.end(); ++it)
		delete it->second;
	vSilo.clear();
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
		lpCoreTexture = CoreSys.CreateCoreTexture(ResPath);
		vSilo.insert(ResMapPair(ResPath, (void*)lpCoreTexture));
	}

	return lpCoreTexture;
}

CoreStream* CoreResource::LinkStream(const char* ResPath)
{
	Stackit;

	void* Value;
	CoreStream* lpCoreStream;

	if(Link(ResPath, Value))
		lpCoreStream = (CoreStream*)Value;
	else
	{
		lpCoreStream = CoreSys.CreateCoreStream(ResPath);
		vSilo.insert(ResMapPair(ResPath, (void*)lpCoreStream));
	}

	return lpCoreStream;
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
