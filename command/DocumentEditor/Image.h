#pragma once
#include "IImage.h"
#include "ImageImpl.h"

class CImage : public IImage
{
public:
	CImage(int width, int height, Path path);
	CImage::~CImage() = default;

	// ���������� ���� ������������ �������� ���������
	Path GetPath()const;

	// ������ ����������� � ��������
	int GetWidth()const;
	// ������ ����������� � ��������
	int GetHeight()const;

	// �������� ������ �����������
	void Resize(int width, int height);

	void SetDeleteResource(bool deleteResource);

private:
	std::unique_ptr<CImageImpl> m_impl;
};