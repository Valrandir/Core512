#include "Core512.h"
#include "Input.h"

void InputGetDirection(int& dx, int& dy)
{
	if(lpHGE->Input_GetKeyState(HGEK_LEFT) || lpHGE->Input_GetKeyState(HGEK_D))
		dx = -1;
	else if(lpHGE->Input_GetKeyState(HGEK_RIGHT) || lpHGE->Input_GetKeyState(HGEK_F))
		dx = 1;
	else
		dx = 0;

	if(lpHGE->Input_GetKeyState(HGEK_UP) || lpHGE->Input_GetKeyState(HGEK_LBUTTON))
		dy = -1;
	else if(lpHGE->Input_GetKeyState(HGEK_DOWN) || lpHGE->Input_GetKeyState(HGEK_RBUTTON))
		dy = 1;
	else
		dy = 0;
}
