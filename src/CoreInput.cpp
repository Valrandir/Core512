#include "CoreSystem.h"
#include "CoreInput.h"

#define Key(KeyCode)CoreSys.KeyState(KeyCode)

CoreInputEnum CoreInput::Command()
{
	if(Key(HGEK_SPACE))
		return CoreInput_ShipReset;

	if(Key(HGEK_T))
		return CoreInput_Background_Toggle;

	return CoreInput_None;
}

void CoreInput::Direction(int& ForceDirection, int& RotationDirection)
{
	ForceDirection = 0;
	if(Key(HGEK_UP) || Key(HGEK_LBUTTON))
		++ForceDirection;
	if(Key(HGEK_DOWN) || Key(HGEK_RBUTTON))
		--ForceDirection;

	RotationDirection = 0;
	if(Key(HGEK_LEFT) || Key(HGEK_D))
		--RotationDirection;
	if(Key(HGEK_RIGHT) || Key(HGEK_F))
		++RotationDirection;
}
