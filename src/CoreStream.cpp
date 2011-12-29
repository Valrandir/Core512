#include "CoreDefs.h"
#include "CoreStream.h"

CoreStream::CoreStream(const char* ResPath) : StreamHandle(hStream), hStream(NULL), hChannel(NULL)
{
	Stackit;
	if(CoreSys.Config->UseMusic)
		TryH(hStream = CoreSys.Hge->Stream_Load(ResPath));
}

CoreStream::~CoreStream()
{
	if(hStream)
		CoreSys.Hge->Stream_Free(hStream);
}

void CoreStream::Play()
{
	if(hStream)
		hChannel = CoreSys.Hge->Stream_Play(hStream, true);
}

void CoreStream::Stop()
{
	if(hStream && hChannel)
	{
		CoreSys.Hge->Channel_Stop(hChannel);
		hChannel = NULL;
	}
}
