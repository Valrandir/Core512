#pragma once
#include <hgeanim.h>

struct Explosion
{
	hgeAnimation* lpAnimation;
	float Width, Height;

	Explosion();
	~Explosion();

	void Play();
	bool IsPlaying();
	void Update();
	void Render(float x, float y) const;
};
