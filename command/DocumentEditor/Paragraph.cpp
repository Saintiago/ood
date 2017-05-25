#include "stdafx.h"
#include "Paragraph.h"


CParagraph::CParagraph(std::string text)
	: m_text(move(text))
{
}

const string & CParagraph::GetText()const
{
	return m_text;
}

void CParagraph::SetText(string text)
{
	m_text = move(text);
}
