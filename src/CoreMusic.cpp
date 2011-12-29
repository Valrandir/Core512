#include "CoreDefs.h"
#include "CoreMusic.h"
#include "CoreFile.h"

CoreMusic::CoreMusic() : lpCoreStream(NULL), IsPlaying(false)
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
	if(!Timer.Finished())
		return;

	if(IsPlaying)
		Stop();
	else
		Play();

	Timer.Launch(250);
}
