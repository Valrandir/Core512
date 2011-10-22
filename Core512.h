#pragma once
#include <hge.h>

#define DeleteNull(ptr)if(ptr){delete (ptr);(ptr)=NULL;}
#define DeleteHgeTexture(ptr)if(ptr){lpHGE->Texture_Free(ptr);(ptr)=NULL;}

const float CoreRad1   = 6.2831853071795864f;
const float CoreRad2   = 3.1415926535897932f;
const float CoreRad4   = 0.7853981633974483f;
const float CoreRad8   = 0.3926990816987241f;
const float CoreRad16  = 0.1963495408493620f;
const float CoreRad32  = 0.0981747704246810f;
const float CoreRad64  = 0.0490873852123405f;
const float CoreRad128 = 0.0245436926061702f;

extern HGE* lpHGE;
