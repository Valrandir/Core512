#pragma once

#define CMD_SHIP_RESET 1
#define CMD_SHIP_EXPLODE 2
#define CMD_BACKGROUND_TOGGLE 3

int InputGetCommand();
void InputGetDirection(int& ForceDirection, int& RotationDirection);
