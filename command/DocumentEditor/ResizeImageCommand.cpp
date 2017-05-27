#include "stdafx.h"
#include "ResizeImageCommand.h"

CResizeImageCommand::CResizeImageCommand(const shared_ptr<IImage> & target, int width, int height)
	: m_target(target)
	, m_newWidth(width)
	, m_newHeight(height)
{
	m_oldWidth = m_target->GetWidth();
	m_oldHeight = m_target->GetHeight();
}

void CResizeImageCommand::DoExecute()
{
	m_target->Resize(m_newWidth, m_newHeight);
}

void CResizeImageCommand::DoUnexecute()
{
	m_target->Resize(m_oldWidth, m_oldHeight);
}
