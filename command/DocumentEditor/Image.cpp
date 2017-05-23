#include "stdafx.h"
#include "Image.h"

CImage::CImage(int width, int height, Path path)
{
	m_impl = make_unique<CImageImpl>(width, height, path);
}

Path CImage::GetPath()const
{
	return m_impl->GetPath();
}

int CImage::GetWidth()const
{
	return m_impl->GetWidth();
}

int CImage::GetHeight()const
{
	return m_impl->GetHeight();
}

void CImage::Resize(int width, int height)
{
	m_impl->Resize(width, height);
}

void CImage::SetDeleteResource(bool deleteResource)
{
	m_impl->SetDeleteResource(deleteResource);
}
