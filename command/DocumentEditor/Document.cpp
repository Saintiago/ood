#include "stdafx.h"
#include "Document.h"
#include "History.h"
#include "ChangeStringCommand.h"
#include "InsertParagraphCommand.h"
#include "InsertImageCommand.h"
#include "ReplaceTextCommand.h"
#include "ResizeImageCommand.h"
#include "DeleteItemCommand.h"
#include "Paragraph.h"

#include <fstream>

using namespace std;
namespace fs = boost::filesystem;

CDocument::CDocument()
{}

CDocument::~CDocument()
{
	if (fs::exists(fs::current_path() / "imagestmp"))
	{
		fs::remove_all(fs::current_path() / "imagestmp");
	}
}

void CDocument::SetTitle(const std::string & title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

void CDocument::InsertParagraph(const string& text, optional<size_t> position)
{
	m_history.AddAndExecuteCommand(make_unique<CInsertParagraphCommand>(m_storage, text, position));
}

void CDocument::InsertImage(const Path& path, int width, int height, optional<size_t> position)
{
	m_history.AddAndExecuteCommand(make_unique<CInsertImageCommand>(m_storage, width, height, path, position));
}

DocumentItemPtr CDocument::GetItem(size_t index)const
{
	return m_storage.GetItem(index);
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	if (!CanUndo())
	{
		throw logic_error("Can't undo.");
	}
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	if (!CanRedo())
	{
		throw logic_error("Can't redo.");
	}
	m_history.Redo();
}

void CDocument::List(ostream& output)
{
	output << "Title : " << GetTitle() << endl;
	unsigned index = 0;
	for (auto & documentItem : m_storage.GetItems())
	{
		shared_ptr<IImage> image = documentItem->GetImage();
		shared_ptr<IParagraph> paragraph = documentItem->GetParagraph();

		if (image != nullptr)
		{
			output << index++ << ". " << "Image : ";
			output << image->GetWidth() << " " << image->GetHeight() << " ";
			output << image->GetPath() << endl;
		}

		if (paragraph != nullptr)
		{
			output << index++ << ". " << "Paragraph : ";
			output << paragraph->GetText() << endl;
		}
	}
}

void CDocument::Help(ostream& output)
{
	output << "Available commands:" << endl;
	output << "InsertParagraph <позиция>|end <текст параграфа>" << endl;
	output << "InsertImage <позиция>|end <ширина> <высота> <путь к файлу изображения>" << endl;
	output << "SetTitle <заголовок документа>" << endl;
	output << "List" << endl;
	output << "ReplaceText <позиция> <текст параграфа>" << endl;
	output << "ResizeImage <позиция> <ширина> <высота>" << endl;
	output << "DeleteItem <позиция>" << endl;
	output << "Help" << endl;
	output << "Undo" << endl;
	output << "Redo" << endl;
	output << "Save <путь>" << endl;
}

void CDocument::ReplaceText(size_t position, string newValue)
{
	if (m_storage.GetSize() <= position)
	{
		throw out_of_range("There is no paragraph at " + position);
	}
	shared_ptr<IParagraph> paragraph = m_storage.GetItem(position)->GetParagraph();
	if (paragraph == nullptr)
	{
		throw out_of_range("There is no paragraph at " + position);
	}
	m_history.AddAndExecuteCommand(make_unique<CReplaceTextCommand>(paragraph, newValue));
}

void CDocument::ResizeImage(size_t position, int width, int height)
{
	if (m_storage.GetSize() <= position)
	{
		throw out_of_range("There is no image at " + position);
	}
	shared_ptr<IImage> image = m_storage.GetItem(position)->GetImage();
	if (image == nullptr)
	{
		throw out_of_range("There is no image at " + position);
	}
	m_history.AddAndExecuteCommand(make_unique<CResizeImageCommand>(image, width, height));
}

void CDocument::DeleteItem(size_t index)
{
	m_history.AddAndExecuteCommand(make_unique<CDeleteItemCommand>(m_storage, index));
}

void CDocument::Save(const Path& baseDir)const
{
	Path imagesDir = baseDir / "images";
	Path indexPath = baseDir / "index.html";
	
	// Create directories
	fs::create_directory(imagesDir);
	
	CopyResources(imagesDir);

	// Create file stream
	ofstream indexFile(indexPath.string());

	ToHtml(indexFile);

	indexFile.close();
}

void CDocument::ToHtml(ostream& output)const
{
	// Put there heading
	output << "<!DOCTYPE html><html><head>"
		<< "<title>" << GetTitle() << "</title>"
		<< "</head><body>";

	// Put there all document items
	for (auto & documentItem : m_storage.GetItems())
	{
		shared_ptr<IImage> image = documentItem->GetImage();
		shared_ptr<IParagraph> paragraph = documentItem->GetParagraph();

		if (image != nullptr)
		{
			output << "<img width=\"" << image->GetWidth() << "\" height=\"" << image->GetHeight() << "\" src=" << image->GetPath() << " />";
		}

		if (paragraph != nullptr)
		{
			output << "<p>" << paragraph->GetText() << "</p>";
		}
	}

	// Put there endings
	output << "</body></html>";
}

void CDocument::CopyResources(const Path& resourcesDir)const
{
	for (auto & documentItem : m_storage.GetItems())
	{
		shared_ptr<IImage> image = documentItem->GetImage();

		if (image != nullptr)
		{
			Path imagePath = image->GetPath();
			fs::copy_file(imagePath, resourcesDir / imagePath.filename());
		}
	}
}

