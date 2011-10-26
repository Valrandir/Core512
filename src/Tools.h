#pragma once
#include "Vertex.h"

void RenderSquare(float x, float y, float size);
void QuadCreate(float Width, float Height, hgeQuad& Quad);
void QuadSet(float x, float y, hgeQuad& Quad);
void QuadSetCenter(Vertex Center, hgeQuad& Quad);
void QuadOffset(float x, float y, hgeQuad& Quad);
float Abs(float val);