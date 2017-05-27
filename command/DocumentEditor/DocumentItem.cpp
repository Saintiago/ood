#include "stdafx.h"
#include "DocumentItem.h"

using namespace std;

CDocumentItem::CDocumentItem(const shared_ptr<IImage> & imagePtr, const shared_ptr<IParagraph> & paragraphPtr)
	: m_imagePtr(imagePtr)
	, m_paragraphPtr(paragraphPtr)
{
}

// ���������� ��������� �� ����������� �����������, ���� nullptr, ���� ������� �� �������� ������������
shared_ptr<IImage> CDocumentItem::GetImage()const
{
	return m_imagePtr;
}

// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
shared_ptr<IParagraph> CDocumentItem::GetParagraph()const
{
	return m_paragraphPtr;
}

void CDocumentItem::SetDeleteResource(bool deleteResource)
{
	if (m_imagePtr != nullptr)
	{
		m_imagePtr->SetDeleteResource(deleteResource);
	}
}