#pragma once
#include "CoreTimer.h"
class CoreStream;

class CoreMusic
{
	private:
	CoreStream* lpCoreStream;
	void Load();
	bool IsPlaying;
	CoreTimer Timer;

	public:
	CoreMusic();
	void Play();
	void Stop();
	void Toggle();
};
