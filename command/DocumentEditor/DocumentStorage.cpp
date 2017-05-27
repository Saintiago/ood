#include "stdafx.h"
#include "DocumentStorage.h"

using namespace std;


CDocumentStorage::CDocumentStorage()
{
}


CDocumentStorage::~CDocumentStorage()
{
}

void CDocumentStorage::InsertDocumentItem(const DocumentItemPtr & documentItem, boost::optional<size_t> position)
{
	// TODO: Если номер позиции превышает количество элементов в документе, 
	// пользователю выдается сообщение об ошибке, а команда игнорируется

	std::deque<DocumentItemPtr>::iterator positionIterator;
	size_t unwrappedPosition = position.get_value_or(m_documentItems.size());
	m_documentItems.insert(m_documentItems.begin() + unwrappedPosition, documentItem);
	GetItem(unwrappedPosition)->SetDeleteResource(false);
}

void CDocumentStorage::DeleteDocumentItem(size_t position)
{
	GetItem(position)->SetDeleteResource(true);
	m_documentItems.erase(m_documentItems.begin() + position);
}

DocumentItemPtr CDocumentStorage::GetItem(size_t index)const
{
	return m_documentItems.at(index);
}

ConstDocumentItemPtr CDocumentStorage::GetConstItem(size_t index)const
{
	return m_documentItems.at(index);
}

size_t CDocumentStorage::GetSize()const
{
	return m_documentItems.size();
}
