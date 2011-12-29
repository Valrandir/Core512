#pragma once
#include <hge.h>

class CoreStream
{
	HSTREAM hStream;
	HCHANNEL hChannel;

	public:
	const HSTREAM& StreamHandle;

	CoreStream(const char* ResPath);
	~CoreStream();
	void Play();
	void Stop();
};
