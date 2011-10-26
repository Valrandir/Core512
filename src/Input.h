#pragma once

#define CMD_SHIP_RESET 1
#define CMD_BACKGROUND_TOGGLE 2

int InputGetCommand();
void InputGetDirection(int& ForceDirection, int& RotationDirection);
