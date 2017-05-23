#include "stdafx.h"
#include "Paragraph.h"


CParagraph::CParagraph(std::string& text)
	: m_text(text)
{
}

string & CParagraph::GetText()const
{
	return m_text;
}

void CParagraph::SetText(string& text)
{
	m_text = move(text);
}
