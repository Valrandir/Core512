#include <hge.h>
#include "Tools.h"
#include "Ship.h"

extern HGE* lpHGE;
extern int Window_Width;
extern int Window_Height;

HTEXTURE hTex;
hgeQuad Quad = {0};
int Width, Height;

float x, y; //Position
float vx, vy; //Velocity
float fx, fy; //Force
float EngineForce; //Engine Force

void ShipInit()
{
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	fx = 0;
	fy = 0;
	EngineForce = 50.0f;

	hTex = lpHGE->Texture_Load("Res\\Ship.png");

	Width = lpHGE->Texture_GetWidth(hTex, true);
	Height = lpHGE->Texture_GetHeight(hTex, true);

	QuadCreate((float)Width, (float)Height, Quad);
	QuadOffset(10, 10, Quad);

	Quad.tex = hTex;
}

void ShipUnload()
{
	lpHGE->Texture_Free(hTex);
	hTex = NULL;
}

void ShipDraw()
{
	//lpHGE->Gfx_RenderQuad(&Quad);
}

//direction must be -1, 0, or 1
void ShipThrust(int dx, int dy)
{
	fx = dx * EngineForce;
	fy = dy * EngineForce;
}

void ShipTick()
{
	float dt = lpHGE->Timer_GetDelta();

	vx += fx;
	vy += fy;

	vx *= 0.95f;
	vy *= 0.95f;

	if(Abs(vx) < 0.001) vx = 0;
	if(Abs(vy) < 0.001) vy = 0;
	if(Abs(fx) < 0.001) fx = 0;
	if(Abs(fy) < 0.001) fy = 0;

	x += vx * dt;
	y += vy * dt;

	//lpHGE->System_Log("%f", x);

	if(x < 0) x = 0;
	if(y < 0) y = 0;

	if((int)x > Window_Width - Width)
	{
		x = float(Window_Width - Width);
		vx = vy = 0;
	}

	if((int)y > Window_Height - Height)
	{
		y = float(Window_Height - Height);
		vx = vy = 0;
	}

	QuadSet(x, y, Quad);
}

void ShipGetCenterPos(float& x, float& y)
{
	x = ::x + Width / 2;
	y = ::y + Height / 2;
}
