#pragma once

struct Rect
{
	float x1, y1;
	float x2, y2;
	float cx, cy;
	float w, h;

	Rect();

	void SetByCenter(float cx, float cy, float w, float h);
	void SetByPoints(float x1, float y1, float x2, float y2);
	void Move(float cx, float cy);
};
