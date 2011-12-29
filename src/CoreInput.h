#pragma once

enum CoreInputEnum
{
	CoreInput_None = 0,
	CoreInput_Shoot = 1,
	CoreInput_ShipReset = 2,
	CoreInput_Background_Toggle = 3,
	CoreInput_Music_Toggle = 4,
	CoreInput_Explode = 5
};

class CoreInput
{
	public:
	static CoreInputEnum Command();
	static void Direction(int& ForceDirection, int& RotationDirection);
};
