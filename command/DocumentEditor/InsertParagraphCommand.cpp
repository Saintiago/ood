#include "stdafx.h"
#include "InsertParagraphCommand.h"
#include "Paragraph.h"

using namespace std;

CInsertParagraphCommand::CInsertParagraphCommand(CDocumentStorage& target, std::string const& text, boost::optional<size_t> position)
	: m_target(target)
{
	if (position.is_initialized())
	{
		m_position = position.get();
	}

	m_position = (position.is_initialized()) ? position.get() : m_target.GetSize();

	m_paragraph = make_shared<CParagraph>(text);
}

void CInsertParagraphCommand::DoExecute()
{
	m_target.InsertDocumentItem(make_shared<CDocumentItem>(nullptr, m_paragraph), m_position);
}

void CInsertParagraphCommand::DoUnexecute()
{
	m_target.DeleteDocumentItem(m_position);
}
