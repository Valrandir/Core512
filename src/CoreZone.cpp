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
	MapSquareSize.Set(16, 16);
	Try(lpMap = new CoreMap(ZoneSize, MapSquareSize));
}

CoreZone::~CoreZone()
{
	DeleteNull(lpCoreBG);
	delete lpMap;
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

const CoreVecInt& CoreZone::MapSquareSizeGet() const
{
	return MapSquareSize;
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

void CoreZone::MapSet(const CoreVecInt& TopLeft, const CoreVecInt& Size, CoreZoneEntity*const Entity)
{
	lpMap->SetArea(TopLeft, Size, Entity);
}

void CoreZone::Update(float Delta)
{
	CoreBodyList::Update(Delta);
	CoreBodyList::RemoveOutsideRect(*this, lpTrackBody);
	UpdateScreenRect();
}

BOOL CoreZone::RenderEntityPart(const CoreVecInt& MapPosition, CoreZoneEntity* Entity, const void* const Param)
{
	CoreZone* Self = (CoreZone*)Param;
	Entity->Render(MapPosition, Self->RenderOffset);
	return FALSE;
}

void CoreZone::RenderGridMap() const
{
	CoreVecInt TopLeft;
	CoreVecInt Size;

	TopLeft = ((ScreenRect.xy1 + ScreenRect.Size / 2) + RenderOffset) / MapSquareSize;
	Size = ScreenRect.Size / MapSquareSize;

	lpMap->Scanner(TopLeft, Size, &CoreZone::RenderEntityPart, this);

	//For a quick test all squares are checked instead of only those visible.
	//lpMap->Scanner(CoreVecInt(), CoreVecInt(lpMap->GetMapSize()), &CoreZone::RenderEntityPart, this);
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
