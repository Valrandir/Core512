#pragma once
#include "CoreVector.h"
#include "CoreText.h"

class HelpText
{
	const char* HelpTextContent;
	CoreText Text;

	public:
	HelpText();
	void Render();
};
