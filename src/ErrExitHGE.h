#pragma once
#include <hge.h>
#include "ErrExit.h"

#ifdef _DEBUG
	#define TryH(Fn) if(Fn)ErrExit::FinalError(#Fn,__FUNCTION__,__FILE__,__LINE__,0,hge->System_GetErrorMessage());
	#define TrnH(Fn) TryH(!(Fn))
#else
	#define TryH(Fn) Fn
	#define TrnH(Fn) Fn
#endif
