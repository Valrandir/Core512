#include "Core512.h"
#include "Input.h"

void InputGetDirection(int& dx, int& dy)
{
	if(lpHGE->Input_GetKeyState(HGEK_LEFT))
		dx = -1;
	else if(lpHGE->Input_GetKeyState(HGEK_RIGHT))
		dx = 1;
	else
		dx = 0;

	if(lpHGE->Input_GetKeyState(HGEK_UP))
		dy = -1;
	else if(lpHGE->Input_GetKeyState(HGEK_DOWN))
		dy = 1;
	else
		dy = 0;
}
