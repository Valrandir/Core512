#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <vector>

#ifdef _DEBUG
	#define Stackit Stackage lpLocalStackage(__FUNCTION__);
	#define FinalErrorM(Message) ErrExit::FinalError(Message,__FUNCTION__,__FILE__,__LINE__);
	#define Try(Fn) if(Fn)ErrExit::FinalError(#Fn,__FUNCTION__,__FILE__,__LINE__,GetLastError());
	#define Trn(Fn) Try(!(Fn))
#else
	#define Stackit
	#define FinalErrorM(Message)ErrExit::FinalError(Message,__FUNCTION__,__FILE__,__LINE__,GetLastError());
	#define Try(Fn) Fn
	#define Trn(Fn) Fn
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
	static std::string GetSystemErrText(int MessageID);
	static void FinalError(const char *FailCall, const char *Function, const char *File, const long Line, const DWORD SystemErrorID=0, const char *ErrorText=0);
};
