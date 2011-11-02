#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <vector>

//HGE Hack because it render in the WM_PAINT message like a retard while in window mode.
void Set_ErrExitHge_HgePtr(void* HgePtr);
const char* System_GetErrorMessage();

#ifdef _DEBUG
	#define Stackit Stackage lpLocalStackage(__FUNCTION__);
	#define FinalErrorM(Message) ErrExit::FinalError(Message,__FUNCTION__,__FILE__,__LINE__);
	#define Trn(Fn) if(Fn)ErrExit::FinalError(#Fn,__FUNCTION__,__FILE__,__LINE__,GetLastError());
	#define Try(Fn) Trn(!(Fn))
	#define TrnH(Fn) if(Fn)ErrExit::FinalError(#Fn,__FUNCTION__,__FILE__,__LINE__,0,System_GetErrorMessage());
	#define TryH(Fn) TrnH(!(Fn))
#else
	#define Stackit
	#define FinalErrorM(Message)ErrExit::FinalError(Message,__FUNCTION__,__FILE__,__LINE__,GetLastError());
	#define Trn(Fn) Fn
	#define Try(Fn) Fn
	#define TrnH(Fn) Fn
	#define TryH(Fn) Fn
#endif

class Stackage
{
	static std::vector<char*> vStack;
	static unsigned int Deep;

	public:
	Stackage(char *Function);
	~Stackage();
	static std::string GetString();
};

class ErrExit
{
	ErrExit(){}
	static std::string GetLocalTime();
	public:
	static void ClipBoardSetText(const char *Text);
	static void GetSystemErrText(int MessageID, char *Buffer, int BufferSize);
	static void FinalError(const char *FailCall, const char *Function, const char *File, const long Line, const DWORD SystemErrorID=0, const char *ErrorText=0);
};
