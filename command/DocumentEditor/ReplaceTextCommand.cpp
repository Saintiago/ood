#include "stdafx.h"
#include "ReplaceTextCommand.h"

CReplaceTextCommand::CReplaceTextCommand(const shared_ptr<IParagraph> & target, std::string & newValue)
	: m_target(target)
	, m_newValue(newValue)
{
	m_oldValue = m_target->GetText();
}

void CReplaceTextCommand::DoExecute()
{
	m_target->SetText(m_newValue);
}

void CReplaceTextCommand::DoUnexecute()
{
	m_target->SetText(m_oldValue);
}