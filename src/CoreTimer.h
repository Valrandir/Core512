#pragma once

class CoreTimer
{
	DWORD Goal;
	bool Active;

	public:
	CoreTimer::CoreTimer();
	void Launch(DWORD CountDown);
	bool Finished();
};
