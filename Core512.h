#pragma once
#include <hge.h>

#define DeleteNull(ptr)if(ptr){delete (ptr);(ptr)=NULL;}

extern HGE* lpHGE;
