#pragma once
#include "AbstractCommand.h"
#include "DocumentStorage.h"

class CInsertImageCommand :
	public CAbstractCommand
{
public:
	CInsertImageCommand(CDocumentStorage& m_target, int width, int height, Path path, boost::optional<size_t> position);
	~CInsertImageCommand() = default;

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	CDocumentStorage& m_target;
	int m_width, m_height;
	Path m_path;
	size_t m_position;
	shared_ptr<IImage> m_image;

	string m_imagesDirName = "images";
	Path m_imagePathTemplate = { Path(m_imagesDirName) / "image_%%%%" };

	Path GetRelativeImagePath(Path source);
};

