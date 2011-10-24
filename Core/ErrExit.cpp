#include <time.h>
#include <sstream>
#include "ErrExit.h"

using namespace std;

//Definition of Static Members
vector<char*> Stackage::vStack;
unsigned int Stackage::Deep = 0;

//Constructor
Stackage::Stackage(char *Function)
{
	vStack.push_back(Function);
	++Deep;
}

//Destructor
Stackage::~Stackage()
{
	vStack.pop_back();
	--Deep;
}

//Return the complete callstack in a continuous string
string Stackage::GetString()
{
	vector<char*>::iterator it;
	string stack;
	string separator = " -> ";

	//Build Stack String
	for(it=vStack.begin(); it!=vStack.end(); ++it)
	{
		stack.append(*it);
		stack.append(separator);
	}

	//Remove last separator
	if(stack.length() >= separator.length())
		stack.erase(stack.end() - separator.length(), stack.end());

	return stack;
}

string ErrExit::GetLocalTime()
{
	char Buff[32];
	time_t now;
	tm stm;

	time(&now);
	localtime_s(&stm, &now);
	strftime(Buff, 32, "%Y.%m.%d %H:%M:%S", &stm);

	return Buff;
}

void ErrExit::ClipBoardSetText(const char *Text)
{
	SIZE_T BufferSize;
	HGLOBAL hClipMem;
	char *TextBuffer;
	Stackit;

	BufferSize = strlen(Text) + 1;
	Trn(hClipMem = GlobalAlloc(GMEM_MOVEABLE, BufferSize));
	Trn(TextBuffer = (char*)GlobalLock(hClipMem));
	memcpy(TextBuffer, Text, BufferSize);
	GlobalUnlock(hClipMem);
	Trn(OpenClipboard(HWND_DESKTOP));
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hClipMem);
	CloseClipboard();
}

string ErrExit::GetSystemErrText(int MessageID)
{
	char Buffer[MAX_PATH];
	DWORD ret = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, MessageID, LANG_NEUTRAL, Buffer, MAX_PATH, NULL);
	return ret ? Buffer : "";
}

void ErrExit::FinalError(const char *FailCall, const char *Function, const char *File, const long Line, const DWORD SystemErrorID, const char *ErrorText)
{
	const char *newl = "\r\n";
	int Response;
	stringstream msg;

	//General Information
	msg << "DateTime: " << GetLocalTime() << newl
	    << "FailCall: " << FailCall << newl
	    << "Function: " << Function << newl
	    << "File: " << File << newl
	    << "Line: " << Line << newl << newl;

	//Get Windows LastError Information
	if(SystemErrorID)
	{
		msg << "GetLastError: " << SystemErrorID << newl
		    << GetSystemErrText(SystemErrorID) << newl;
	}
	else if(ErrorText)
	{
		msg << "ErrorText: " << newl << ErrorText << newl << newl;
	}

	//Get CallStack
	msg << "Stack: " << newl << Stackage::GetString() << newl;

	//Display MessageBox and Copy to Clipboard
	string info = msg.str();
	msg << newl << "Copy this information to clipboard?";
	Response = MessageBox(HWND_DESKTOP, msg.str().c_str(), "Fatal Error", MB_YESNO | MB_ICONHAND | MB_DEFBUTTON2);
	if(Response == IDYES)
		ClipBoardSetText(info.c_str());

	//Fatal Fail
	ExitProcess(1);
}
