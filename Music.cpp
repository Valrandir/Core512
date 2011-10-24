#include "Core512.h"
#include "Music.h"

const bool UseMusic = false;

Music::Music() : hStream(NULL)
{
	if(UseMusic)
		hStream = exHGE->Stream_Load("Res\\TheFallen.mp3");
}

Music::~Music()
{
	if(hStream)
		exHGE->Stream_Free(hStream);
}

void Music::Play()
{
	if(hStream)
		exHGE->Stream_Play(hStream, true);
}
