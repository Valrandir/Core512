#include "Core512.h"
#include "Input.h"

void InputGetDirection(int& dx, int& dy, int& dRotate)
{
	dx = 0;
	if(lpHGE->Input_GetKeyState(HGEK_LEFT))
		dx += -1;
	if(lpHGE->Input_GetKeyState(HGEK_RIGHT))
		dx += 1;

	dy = 0;
	if(lpHGE->Input_GetKeyState(HGEK_UP) || lpHGE->Input_GetKeyState(HGEK_LBUTTON))
		dy += -1;
	if(lpHGE->Input_GetKeyState(HGEK_DOWN) || lpHGE->Input_GetKeyState(HGEK_RBUTTON))
		dy += 1;

	dRotate = 0;
	if(lpHGE->Input_GetKeyState(HGEK_D))
		dRotate += -1;
	if(lpHGE->Input_GetKeyState(HGEK_F))
		dRotate += 1;
}
