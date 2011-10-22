#include "Core512.h"
#include "Input.h"

int InputGetCommand()
{
	if(lpHGE->Input_GetKeyState(HGEK_SPACE))
		return CMD_SHIP_RESET;

	return 0;
}

void InputGetDirection(int& ForceDirection, int& RotationDirection)
{
	ForceDirection = 0;
	if(lpHGE->Input_GetKeyState(HGEK_UP) || lpHGE->Input_GetKeyState(HGEK_LBUTTON))
		ForceDirection += -1;
	if(lpHGE->Input_GetKeyState(HGEK_DOWN) || lpHGE->Input_GetKeyState(HGEK_RBUTTON))
		ForceDirection += 1;

	RotationDirection = 0;
	if(lpHGE->Input_GetKeyState(HGEK_LEFT) || lpHGE->Input_GetKeyState(HGEK_D))
		RotationDirection += -1;
	if(lpHGE->Input_GetKeyState(HGEK_RIGHT) || lpHGE->Input_GetKeyState(HGEK_F))
		RotationDirection += 1;
}
