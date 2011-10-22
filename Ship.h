#pragma once

void ShipInit();
void ShipUnload();
void ShipRender();

void ShipThrust(int dx, int dy);
void ShipTick();
void ShipGetCenterPos(float& x, float& y);
