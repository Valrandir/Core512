#pragma once
#include "CoreVector.h"

class CoreRect
{
	public:
	CoreVector xy1, xy2, Center, Size;

	CoreRect();

	void SetByCenter(const CoreVector& Center, const CoreVector& Size);
	void SetByPoints(const CoreVector& xy1, const CoreVector& xy2);
	void Move(const CoreVector& Center);
	void CoreRect::Offset(const CoreVector& Vec);
};
