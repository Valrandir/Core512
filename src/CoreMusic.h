#pragma once
#include "CoreStream.h"
#include "CoreFileEnum.h"

class CoreMusic
{
	private:
	CoreStream* lpCoreStream;
	void Load();
	bool IsPlaying;
	int TickLastToggle;

	public:
	CoreMusic();
	void Play();
	void Stop();
	void Toggle();
};
