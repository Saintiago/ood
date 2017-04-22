#pragma once
#include "stdafx.h"
#include "Shape.h"

std::string CShape::ToString()
{
	return "";
}

void CShape::Draw(ICanvas & canvas)
{
	(void)canvas;
}

void CShape::SetColor(Color color)
{
	m_color = color;
}

Color CShape::GetColor()
{
	return m_color;
}

CShape::CShape()
{
}


CShape::~CShape()
{
}
