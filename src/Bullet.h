#pragma once
#include "CoreSystem.h"

class Bullet : public CoreRotBody
{
	public:
	Bullet(const CoreVector& Center, const CoreVector& Direction);
	~Bullet();
	void Update(float Delta);
};
