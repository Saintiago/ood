#pragma once
#include "stdafx.h"

class CImageImpl
{
public:
	CImageImpl(int width, int height, Path path);
	~CImageImpl();

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
	int m_width;
	int m_height;
	Path m_path;
	bool m_deleteResource = true;
};

