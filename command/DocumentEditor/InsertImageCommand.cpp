#include "stdafx.h"
#include "InsertImageCommand.h"
#include "Image.h"

namespace fs = boost::filesystem;

string CInsertImageCommand::imagesDirName = "images";
Path CInsertImageCommand::imagePathTemplate = { Path(CInsertImageCommand::imagesDirName) / "image_%%%%" };

CInsertImageCommand::CInsertImageCommand(CDocumentStorage& target, int width, int height, Path path, boost::optional<size_t> position)
	: m_target(target)
	, m_width(width)
	, m_height(height)
	, m_path(path)
{
	if (position.is_initialized())
	{
		m_position = position.get();
	}

	Path imagesDir = fs::current_path() / imagesDirName;
	if (!fs::exists(imagesDir))
	{
		fs::create_directory(imagesDir);
	}

	m_position = (position.is_initialized()) ? position.get() : m_target.GetSize();
	Path relativeImagePath = GetRelativeImagePath(m_path);
	Path destination = fs::current_path() / relativeImagePath;
	fs::copy_file(m_path, destination);
	m_image = std::make_shared<CImage>(m_width, m_height, relativeImagePath);
}

void CInsertImageCommand::DoExecute()
{
	m_target.InsertDocumentItem(make_shared<CDocumentItem>(m_image, nullptr), m_position);
}

void CInsertImageCommand::DoUnexecute()
{
	m_target.DeleteDocumentItem(m_position);
}

Path CInsertImageCommand::GetRelativeImagePath(Path source)
{
	Path uniquePath = fs::unique_path(imagePathTemplate);
	string extension = fs::extension(source);
	return { uniquePath.string() + extension };
}