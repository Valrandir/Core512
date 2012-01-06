#include "CoreDefs.h"
#include "CoreZone.h"

CoreZone::BorderRect::BorderRect()
{
	const DWORD Default = 0xFFFFFFFF;
	Colors[0] = Default;
	Colors[1] = Default;
	Colors[2] = Default;
	Colors[3] = Default;
}

void CoreZone::BorderRect::SetColors(DWORD TopLeft, DWORD TopRight, DWORD BottomRight, DWORD BottomLeft)
{
	DWORD* c = this->Colors;
	*c++ = TopLeft;
	*c++ = TopRight;
	*c++ = BottomRight;
	*c = BottomLeft;
}

CoreZone::BorderRect& CoreZone::BorderRect::Clone(BorderRect& Specimen) const
{
	CoreRect::Clone(Specimen);
	Specimen.Colors[0] = Colors[0];
	Specimen.Colors[1] = Colors[1];
	Specimen.Colors[2] = Colors[2];
	Specimen.Colors[3] = Colors[3];
	return Specimen;
}

CoreZone::CoreZone(const CoreVector& ZoneSize) : lpCoreBG(NULL), lpTrackBody(NULL)
{
	Stackit;

	//Init Zone Rect
	CoreRect::SetByCenter(ZoneSize);

	//Init ScreenRect
	CoreVector ScreenSize;
	CoreSys.GetScreenSize(ScreenSize);
	ScreenRect.SetByCenter(ScreenSize);

	//Init NoScrollRect
	NoScrollRect.SetByCenter(ScreenSize / 1.25);

	//Init ZoneToScr
	ZoneToScr = ScreenRect.Size / 2;

	//Init Borders
	InitBorders();

	//Init CoreBackground
	Try(lpCoreBG = new CoreBackground());

	//Init GridMap
	Try((int)ZoneSize.x % GridMapSquareSize == 0);
	Try((int)ZoneSize.y % GridMapSquareSize == 0);
	GridMapSquareCount = ZoneSize / (float)GridMapSquareSize;
	GridMapLineByteSize = sizeof(CoreZoneEntity*) * (int)GridMapSquareCount.x;
	GridMapByteSize = GridMapLineByteSize * (int)GridMapSquareCount.y;
	Try(GridMap = (CoreZoneEntity**)malloc(GridMapByteSize));
	memset(GridMap, 0, GridMapByteSize);
}

CoreZone::~CoreZone()
{
	DeleteNull(lpCoreBG);
	free(GridMap);
}

void CoreZone::TrackBody(CoreBody& lpBody)
{
	lpTrackBody = &lpBody;
	if(lpTrackBody)
	{
		ScreenRect.Move(lpTrackBody->Center);
		NoScrollRect.Move(Center);
	}
}

void CoreZone::ToggleBG()
{
	lpCoreBG->Toggle();
}

void CoreZone::InitBorders()
{
	float BorderSize = (float)CoreSys.Config->ZoneBorderSize;
	DWORD Color = 0xFFFFFFFF;

	//Set Borders
	vBorderRect[0].SetByPoints(xy1.x, xy1.y, xy1.x + BorderSize, xy1.y + BorderSize);
	vBorderRect[1].SetByPoints(xy1.x + BorderSize, xy1.y, xy2.x - BorderSize, xy1.y + BorderSize);
	vBorderRect[2].SetByPoints(xy2.x - BorderSize, xy1.y, xy2.x, xy1.y + BorderSize);
	vBorderRect[6].SetByPoints(xy1.x, xy2.y - BorderSize, xy1.x + BorderSize, xy2.y);
	vBorderRect[5].SetByPoints(xy1.x + BorderSize, xy2.y - BorderSize, xy2.x - BorderSize, xy2.y);
	vBorderRect[4].SetByPoints(xy2.x - BorderSize, xy2.y - BorderSize, xy2.x, xy2.y);
	vBorderRect[3].SetByPoints(xy2.x - BorderSize, xy1.y + BorderSize, xy2.x, xy2.y - BorderSize);
	vBorderRect[7].SetByPoints(xy1.x, xy1.y + BorderSize, xy1.x + BorderSize, xy2.y - BorderSize);

	//Set Colors and Alpha
	vBorderRect[0].SetColors(SETA(Color, 0xFF), SETA(Color, 0xFF), SETA(Color, 0x00), SETA(Color, 0xFF));
	vBorderRect[1].SetColors(SETA(Color, 0xFF), SETA(Color, 0xFF), SETA(Color, 0x00), SETA(Color, 0x00));
	vBorderRect[2].SetColors(SETA(Color, 0xFF), SETA(Color, 0xFF), SETA(Color, 0xFF), SETA(Color, 0x00));
	vBorderRect[3].SetColors(SETA(Color, 0x00), SETA(Color, 0xFF), SETA(Color, 0xFF), SETA(Color, 0x00));
	vBorderRect[4].SetColors(SETA(Color, 0x00), SETA(Color, 0xFF), SETA(Color, 0xFF), SETA(Color, 0xFF));
	vBorderRect[5].SetColors(SETA(Color, 0x00), SETA(Color, 0x00), SETA(Color, 0xFF), SETA(Color, 0xFF));
	vBorderRect[6].SetColors(SETA(Color, 0xFF), SETA(Color, 0x00), SETA(Color, 0xFF), SETA(Color, 0xFF));
	vBorderRect[7].SetColors(SETA(Color, 0xFF), SETA(Color, 0x00), SETA(Color, 0x00), SETA(Color, 0xFF));

	////Colorfull Gradient for debugging
	//vBorderRect[0].SetColors(0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFF000000);
	//vBorderRect[1].SetColors(0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFF000000);
	//vBorderRect[2].SetColors(0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFF000000);
	//vBorderRect[3].SetColors(0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFF000000);
	//vBorderRect[4].SetColors(0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFF000000);
	//vBorderRect[5].SetColors(0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFF000000);
	//vBorderRect[6].SetColors(0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFF000000);
	//vBorderRect[7].SetColors(0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFF000000);
}

void CoreZone::UpdateScreenRect()
{
	CoreVector Offset;

	if(lpTrackBody)
	{
		if(NoScrollRect.PointOffset(lpTrackBody->Center, Offset))
		{
			ScreenRect.Offset(Offset);
			NoScrollRect.Offset(Offset);
		}
	}
	else
	{
		ScreenRect.Move(Center);
		NoScrollRect.Move(Center);
	}

	RenderOffset = ZoneToScr - ScreenRect.Center;
}

//Render visible borders
void CoreZone::RenderVisibleBorders() const
{
	BorderRect Specimen;

	for(int i = 0; i < 8; ++i)
		if(ScreenRect.Intersect(vBorderRect[i]))
		{
			vBorderRect[i].Clone(Specimen).Offset(RenderOffset).RoundToPixel();
			CoreSys.Draw->RenderGradient(Specimen, Specimen.Colors);
		}
}

void CoreZone::GridMapSet(const CoreVector& Start, const CoreVector& Size, CoreZoneEntity*const Entity)
{
	int y, x;
	CoreZoneEntity** ptr;

	ptr = GridMap + (int)GridMapSquareCount.x * (int)Start.y + (int)Start.x;
	for(y = 0; y < (int)Size.y; ++y)
	{
		for(x = 0; x < (int)Size.x; ++x, ++ptr)
			*ptr = Entity;
		ptr += (int)GridMapSquareCount.y - (int)Size.x;
	}
}

void CoreZone::Update(float Delta)
{
	CoreBodyList::Update(Delta);
	CoreBodyList::RemoveOutsideRect(*this, lpTrackBody);
	UpdateScreenRect();
}

//For a quick test all squares are checked instead of only those visible.
void CoreZone::RenderGridMap() const
{
	int y, x;
	CoreZoneEntity* ptr;

	int offset;
	int c = 0;

	for(y = 0; y < (int)GridMapSquareCount.y; ++y)
	{
		for(x = 0; x < (int)GridMapSquareCount.x; ++x)
		{
			offset = y * (int)GridMapSquareCount.x + x;
			ptr = GridMap[offset];
			if(ptr)
			{
				ptr->Render(CoreVector((float)x, (float)y));
				++c;
			}
		}
		c = 0;
	}
}

void CoreZone::RenderSimple() const
{
	//Background Stuff
	lpCoreBG->RenderMosaic(ScreenRect.Center);
	RenderVisibleBorders();

	//Grid Stuff
	RenderGridMap();

	//All CoreBody
	CoreBodyList::Render(RenderOffset);
}

void CoreZone::Render() const
{
	const DWORD DeniedBackColor = 0xFFFFFFFF;
	CoreRect Mix;

	if(Intersect(ScreenRect, Mix))
	{
		if(ScreenRect.Size != Mix.Size)
		{
			CoreSys.ClearScreen(DeniedBackColor);
			Mix.Offset(RenderOffset);
			CoreSys.Clip(Mix);
		}
		else
			CoreSys.ClipReset();

		RenderSimple();
	}
	else
		CoreSys.ClearScreen(DeniedBackColor);
}

CoreVector const& CoreZone::GetOffset()
{
	return RenderOffset;
}
