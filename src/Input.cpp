#include "Core512.h"
#include "Input.h"

int InputGetCommand()
{
	if(exHGE->Input_GetKeyState(HGEK_SPACE))
		return CMD_SHIP_RESET;

	if(exHGE->Input_GetKeyState(HGEK_X))
		return CMD_SHIP_EXPLODE;

	if(exHGE->Input_GetKeyState(HGEK_T))
		return CMD_BACKGROUND_TOGGLE;

	return 0;
}

void InputGetDirection(int& ForceDirection, int& RotationDirection)
{
	ForceDirection = 0;
	if(exHGE->Input_GetKeyState(HGEK_UP) || exHGE->Input_GetKeyState(HGEK_LBUTTON))
		ForceDirection += -1;
	if(exHGE->Input_GetKeyState(HGEK_DOWN) || exHGE->Input_GetKeyState(HGEK_RBUTTON))
		ForceDirection += 1;

	RotationDirection = 0;
	if(exHGE->Input_GetKeyState(HGEK_LEFT) || exHGE->Input_GetKeyState(HGEK_D))
		RotationDirection += -1;
	if(exHGE->Input_GetKeyState(HGEK_RIGHT) || exHGE->Input_GetKeyState(HGEK_F))
		RotationDirection += 1;
}
