#pragma once
#include <hgeanim.h>
#include "CoreVector.h"

class CoreFlare
{
	BOOL Initialized;
	hgeAnimation* lpAnimation;
	CoreVector Position;

	public:
	CoreFlare();
	CoreFlare(const CoreVector& Position, const char* ResPath, int SpritePerX, int SpritePerY);
	void Initialize(const CoreVector& Position, const char* ResPath, int SpritePerX, int SpritePerY);
	virtual ~CoreFlare();

	void Play();
	bool IsPlaying() const;
	void Update(float Delta);
	void Render() const;
};
