#include "stdafx.h"
#include "ImageImpl.h"


CImageImpl::CImageImpl(int width, int height, Path path)
	: m_width(width)
	, m_height(height)
	, m_path(path)
{
	// TODO: move min max values to config

	if (m_width < 1 || m_width > 1000 || m_height < 1 || m_height > 1000)
	{
		throw out_of_range("Incorrect image size");
	}
}

Path CImageImpl::GetPath()const
{
	return m_path;
}

int CImageImpl::GetWidth()const
{
	return m_width;
}

int CImageImpl::GetHeight()const
{
	return m_height;
}

void CImageImpl::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void CImageImpl::SetDeleteResource(bool deleteResource)
{
	m_deleteResource = deleteResource;
}

CImageImpl::~CImageImpl()
{
	if (m_deleteResource)
	{
		boost::filesystem::remove(m_path);
	}
}
