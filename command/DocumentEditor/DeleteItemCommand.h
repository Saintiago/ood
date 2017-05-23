#pragma once
#include "AbstractCommand.h"
#include "DocumentStorage.h"

class CDeleteItemCommand :
	public CAbstractCommand
{
public:
	CDeleteItemCommand(CDocumentStorage& target, size_t position);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	CDocumentStorage& m_target;
	size_t m_position;
	DocumentItemPtr m_item;
};



