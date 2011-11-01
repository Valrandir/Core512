#pragma once

#define CMD_SHIP_RESET 1
#define CMD_SHIP_EXPLODE 2
#define CMD_BACKGROUND_TOGGLE 3

enum CoreInputEnum
{
	CoreInput_None = 0,
	CoreInput_ShipReset = 1
};

class CoreInput
{
	public:
	static CoreInputEnum Command();
	static void Direction(int& ForceDirection, int& RotationDirection);
};
