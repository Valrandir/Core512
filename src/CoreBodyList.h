#pragma once
#include <list>
#include "CoreBody.h"

typedef std::list<CoreBody*> CoreBodyVec;

class CoreBodyList
{
	CoreBodyVec vBody;

	public:
	~CoreBodyList();
	void Add(CoreBody& lpCoreBody);
	void Update(float Delta);
	void Render() const;
	void Render(const CoreVector& Offset) const;
};
