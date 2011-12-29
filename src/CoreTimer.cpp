#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "CoreTimer.h"

CoreTimer::CoreTimer() : Active(false)
{}

void CoreTimer::Launch(DWORD CountDown)
{
	Goal = GetTickCount() + CountDown;
	Active = true;
}

bool CoreTimer::Finished()
{
	if(Active)
		Active = GetTickCount() < Goal;
	return !Active;
}
