#include "CoreDefs.h"
#include "CoreMusic.h"
#include "CoreFile.h"

CoreMusic::CoreMusic() : lpCoreStream(NULL), IsPlaying(false), TickLastToggle(0)
{
}

void CoreMusic::Load()
{
	Stackit;
	const char* FileName = "Res/Music.mp3";
	std::string FullPath = CoreFile::AppPath(FileName);

	if(CoreFile::FileExist(FullPath))
		lpCoreStream = CoreSys.Vault->LinkStream(FullPath.c_str());
}

void CoreMusic::Play()
{
	if(!lpCoreStream)
		Load();

	if(lpCoreStream)
	{
		lpCoreStream->Play();
		IsPlaying = true;
	}
}

void CoreMusic::Stop()
{
	if(lpCoreStream)
	{
		lpCoreStream->Stop();
		IsPlaying = false;
	}
}

void CoreMusic::Toggle()
{
	int Tick = GetTickCount();
	if(TickLastToggle && Tick - TickLastToggle < 250) return;
	TickLastToggle = Tick;

	if(IsPlaying)
		Stop();
	else
		Play();
}
