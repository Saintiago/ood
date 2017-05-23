#pragma once
#include "DocumentItem.h"

using DocumentItemsList = std::deque<DocumentItemPtr>;

class CDocumentStorage
{
public:
	CDocumentStorage();
	~CDocumentStorage();

	void InsertDocumentItem(const DocumentItemPtr & documentItem, boost::optional<size_t> position);
	void DeleteDocumentItem(size_t position);
	DocumentItemPtr GetItem(size_t index)const;
	std::deque<DocumentItemPtr> GetItems()const;
	size_t GetSize();

private:
	std::deque<DocumentItemPtr> m_documentItems;

};

