#pragma once
#include <list>
#include "CoreBody.h"
#include "CoreRect.h"

typedef std::list<CoreBody*> CoreBodyVec;

class CoreBodyList
{
	CoreBodyVec vBody;

	public:
	~CoreBodyList();
	void Add(CoreBody& lpCoreBody);
	void Remove(CoreBody& lpCoreBody);
	void RemoveOutsideRect(const CoreRect& Rect, const CoreBody* const Ignore);
	void Update(float Delta);
	void Render() const;
	void Render(const CoreVector& Offset) const;
};
