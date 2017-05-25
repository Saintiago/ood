#pragma once
#include "IParagraph.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(std::string text);
	~CParagraph() = default;

	const string & GetText()const;
	void SetText(string text);

private:
	std::string m_text;
};

