#pragma once
#include "AbstractCommand.h"
#include "IParagraph.h"

class CResizeImageCommand :
	public CAbstractCommand
{
public:
	CResizeImageCommand(const std::shared_ptr<IImage> & target, int width, int height);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<IImage> m_target;
	int m_newWidth, m_newHeight, m_oldWidth, m_oldHeight;
};


