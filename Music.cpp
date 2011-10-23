#include "Core512.h"
#include "Music.h"

const bool UseMusic = false;

Music::Music() : hStream(NULL)
{
	if(UseMusic)
		hStream = lpHGE->Stream_Load("Res\\TheFallen.mp3");
}

Music::~Music()
{
	if(hStream)
		lpHGE->Stream_Free(hStream);
}

void Music::Play()
{
	if(hStream)
		lpHGE->Stream_Play(hStream, true);
}
