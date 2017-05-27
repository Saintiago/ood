#pragma once
#include "stdafx.h"
#include "IDocument.h"
#include "History.h"
#include "DocumentStorage.h"

class CDocument : public IDocument
{
public:

	CDocument();
	~CDocument();

	void SetTitle(const std::string & title) override;
	std::string GetTitle() const override;

	void InsertParagraph(const string& text, optional<size_t> position = none);
	void InsertImage(const Path& path, int width, int height, optional<size_t> position = none);

	DocumentItemPtr GetItem(size_t index)const;

	void List(ostream& output);

	void ReplaceText(size_t position, string newValue);
	void ResizeImage(size_t position, int width, int height);
	void DeleteItem(size_t index);

	bool CanUndo() const override;	
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

	void Save(const Path& path)const;

private:
	std::string m_title;
	CHistory m_history;

	CDocumentStorage m_storage;

	void ToHtml(ostream& output)const;
	std::string Encode(std::string str)const;
	void CopyResources(const Path& resourcesDir)const;
};