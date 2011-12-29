#include "CoreBodyList.h"
	
CoreBodyList::~CoreBodyList()
{
	for(auto it = vBody.begin(); it != vBody.end(); ++it)
		delete *it;
	vBody.clear();
}

void CoreBodyList::Add(CoreBody& lpCoreBody)
{
	vBody.push_back(&lpCoreBody);
}

void CoreBodyList::Remove(CoreBody& lpCoreBody)
{
	vBody.remove(&lpCoreBody);
}

void CoreBodyList::RemoveOutsideRect(const CoreRect& Rect, const CoreBody* const Ignore)
{
	CoreBodyVec::iterator it, it_erase;

	it = vBody.begin();
	while(it != vBody.end())
	{
		if(!Rect.Intersect(**it) && (Ignore && (*it) != Ignore))
		{
			it_erase = it++;
			vBody.erase(it_erase);
		}
		else
			++it;
	}
}

void CoreBodyList::Update(float Delta)
{
	for(auto it = vBody.begin(); it != vBody.end(); ++it)
		(**it).Update(Delta);
}

void CoreBodyList::Render() const
{
	for(auto it = vBody.begin(); it != vBody.end(); ++it)
		(**it).Render();
}

void CoreBodyList::Render(const CoreVector& Offset) const
{
	for(auto it = vBody.begin(); it != vBody.end(); ++it)
		(**it).Render(Offset);
}
