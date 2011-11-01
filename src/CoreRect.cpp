#include "CoreRect.h"

CoreRect::CoreRect() {}

void CoreRect::SetByCenter(const CoreVector& Center, const CoreVector& Size)
{
	this->Center = Center;
	this->Size = Size;
	xy1 = Center - Size / 2;
	xy2 = xy1 + Size;
}

void CoreRect::SetByPoints(const CoreVector& xy1, const CoreVector& xy2)
{
	this->xy1 = xy1;
	this->xy2 = xy2;
	Size = xy2 - xy1;
	Center = xy1 + Size / 2;
}

void CoreRect::Move(const CoreVector& Center)
{
	SetByCenter(Center, Size);
}

void CoreRect::Offset(const CoreVector& Vec)
{
	xy1 += Vec;
	xy2 += Vec;
	Center += Vec;
	Size += Vec;
}