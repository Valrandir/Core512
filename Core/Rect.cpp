#include "Rect.h"

Rect::Rect() : x1(0), y1(0), x2(0), y2(0), cx(0), cy(0), w(0), h(0) {}

void Rect::SetByCenter(float cx, float cy, float w, float h)
{
	this->x1 = cx - w / 2;
	this->y1 = cy - h / 2;
	this->x2 = this->x1 + w;
	this->y2 = this->y1 + h;
	this->cx = cx;
	this->cy = cy;
	this->w = w;
	this->h = h;
}

void Rect::SetByPoints(float x1, float y1, float x2, float y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->w = x2 - x1;
	this->h = y2 - y1;
	this->cx = x1 + this->w / 2;
	this->cy = y1 + this->h / 2;
}
