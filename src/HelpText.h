#pragma once
#include <string>
#include "CoreVector.h"
#include "CoreText.h"

class HelpText
{
	std::string TextStr;
	CoreText Text;

	public:
	HelpText();
	void Render();
};
