#pragma once
#include "AbstractCommand.h"
#include "IParagraph.h"

class CReplaceTextCommand :
	public CAbstractCommand
{
public:
	CReplaceTextCommand(const std::shared_ptr<IParagraph> & target, std::string & newValue);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::string m_newValue;
	std::string m_oldValue;
	std::shared_ptr<IParagraph> m_target;
};
