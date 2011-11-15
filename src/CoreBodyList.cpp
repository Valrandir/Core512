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
