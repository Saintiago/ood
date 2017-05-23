#pragma once
#include "IImage.h"
#include "ImageImpl.h"

class CImage : public IImage
{
public:
	CImage(int width, int height, Path path);
	CImage::~CImage() = default;

	// Возвращает путь относительно каталога документа
	Path GetPath()const;

	// Ширина изображения в пикселях
	int GetWidth()const;
	// Высота изображения в пикселях
	int GetHeight()const;

	// Изменяет размер изображения
	void Resize(int width, int height);

	void SetDeleteResource(bool deleteResource);

private:
	std::unique_ptr<CImageImpl> m_impl;
};