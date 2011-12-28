#include "CoreDefs.h"
#include "CoreFlareList.h"

CoreFlareList::~CoreFlareList()
{
	for(auto it = vFlare.begin(); it != vFlare.end(); ++it)
		delete *it;
	vFlare.clear();
}

void CoreFlareList::Add(const CoreVector& Position, const char* ResPath, int SpritePerX, int SpritePerY)
{
	Stackit;
	CoreFlare* Flare;

	Flare = new CoreFlare(Position, ResPath, SpritePerX, SpritePerY);
	Try(Flare);

	vFlare.push_back(Flare);

	Flare->Play();
}

void CoreFlareList::Update(float Delta)
{
	Stackit;
	auto it = vFlare.begin();
	while(it != vFlare.end())
	{
		auto idx = it++;
		(*idx)->Update(Delta);
		if(!(*idx)->IsPlaying())
			vFlare.erase(idx);
	}
}

void CoreFlareList::Render() const
{
	Stackit;
	for(auto it = vFlare.rbegin(); it != vFlare.rend(); ++it)
		(*it)->Render();
}
