#pragma once
#include "AbstractCommand.h"
#include "DocumentStorage.h"

class CInsertParagraphCommand :
	public CAbstractCommand
{
public:
	CInsertParagraphCommand(CDocumentStorage& target, std::string const& text, boost::optional<size_t> position);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<IParagraph> m_paragraph;
	CDocumentStorage& m_target;
	size_t m_position;
};

