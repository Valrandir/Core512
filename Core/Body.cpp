#include <hge.h>
#include "../Tools.h"
#include "Body.h"

extern HGE* lpHGE;

Body::Body(Vertex Center, float Width, float Height)
{
	QuadCreate(Width, Height, Quad);
	QuadSetCenter(Center, Quad);
}

void Body::Draw()
{
	lpHGE->Gfx_RenderQuad(&Quad);
}
