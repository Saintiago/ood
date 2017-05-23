#pragma once
#include "stdafx.h"

using namespace std;

/* Параграф текста*/
class IParagraph
{
public:
	virtual string & GetText()const = 0;
	virtual void SetText(string& text) = 0;
	virtual ~IParagraph() = default;
};