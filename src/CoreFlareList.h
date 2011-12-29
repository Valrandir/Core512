#pragma once
#include <list>
#include "CoreFlare.h"

class CoreVector;

typedef std::list<CoreFlare*> CoreFlareVec;

class CoreFlareList
{
	CoreFlareVec vFlare;
	public:
	~CoreFlareList();
	void Add(const CoreVector& Position, const char* ResPath, int SpritePerX, int SpritePerY);
	void Update(float Delta);
	void Render(const CoreVector& Offset) const;
};
