#include "stdafx.h"
#include "InsertParagraphCommand.h"
#include "Paragraph.h"

using namespace std;

CInsertParagraphCommand::CInsertParagraphCommand(CDocumentStorage& target, std::string const& text, boost::optional<size_t> position)
	: m_target(target)
	, m_text(text)
{
	if (position.is_initialized())
	{
		m_position = position.get();
	}

	m_position = (position.is_initialized()) ? position.get() : m_target.GetSize();
}

void CInsertParagraphCommand::DoExecute()
{
	auto paragraphPtr = shared_ptr<IParagraph>(new CParagraph(m_text));
	m_target.InsertDocumentItem(make_shared<CDocumentItem>(nullptr, paragraphPtr), m_position);
}

void CInsertParagraphCommand::DoUnexecute()
{
	m_target.DeleteDocumentItem(m_position);
}
