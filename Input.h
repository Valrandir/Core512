#pragma once

#define CMD_SHIP_RESET 1

int InputGetCommand();
void InputGetDirection(int& ForceDirection, int& RotationDirection);
