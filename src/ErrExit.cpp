#include <time.h>
#include <sstream>
#include "ErrExit.h"

using namespace std;

//HGE Hack because it render in the WM_PAINT message like a retard while in window mode.
#include <hge.h>
void* ErrExitHge_HgePtr = NULL;
void Set_ErrExitHge_HgePtr(void* HgePtr){ErrExitHge_HgePtr = HgePtr;}
void FixHgePaintingIntoWM_PAINTEventDirectlyLikeAMofo(){((HGE*)ErrExitHge_HgePtr)->System_SetState(HGE_RENDERFUNC, NULL);}
const char* System_GetErrorMessage(){return ((HGE*)ErrExitHge_HgePtr)->System_GetErrorMessage();}

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
	hClipMem = GlobalAlloc(GMEM_MOVEABLE, BufferSize);
	TextBuffer = (char*)GlobalLock(hClipMem);
	memcpy(TextBuffer, Text, BufferSize);
	GlobalUnlock(hClipMem);
	OpenClipboard(HWND_DESKTOP);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hClipMem);
	CloseClipboard();
}

void ErrExit::GetSystemErrText(int MessageID, char *Buffer, int BufferSize)
{
	DWORD ret = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, MessageID, LANG_NEUTRAL, Buffer, BufferSize, NULL);
	if(!ret)
		Buffer = NULL;
}

void ErrExit::FinalError(const char *FailCall, const char *Function, const char *File, const long Line, const DWORD SystemErrorID, const char *ErrorText)
{
	const char *newl = "\r\n";
	char Buffer[MAX_PATH];
	int Response;
	stringstream msg;

	//OMG WTF
	FixHgePaintingIntoWM_PAINTEventDirectlyLikeAMofo();

	//General Information
	msg << "DateTime: " << GetLocalTime() << newl
	    << "FailCall: " << FailCall << newl
	    << "Function: " << Function << newl
	    << "File: " << File << newl
	    << "Line: " << Line << newl << newl;

	//Get Windows LastError Information
	if(SystemErrorID)
	{
		GetSystemErrText(SystemErrorID, Buffer, MAX_PATH);
		msg << "GetLastError: " << SystemErrorID << newl
		    << Buffer << newl;
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
