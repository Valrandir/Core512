#pragma once

enum CoreInputEnum
{
	CoreInput_None = 0,
	CoreInput_ShipReset = 1,
	CoreInput_Background_Toggle = 2,
	CoreInput_Explode = 3
};

class CoreInput
{
	public:
	static CoreInputEnum Command();
	static void Direction(int& ForceDirection, int& RotationDirection);
};
