#pragma once
#include "stdafx.h"
#include "Shape.h"

void CShape::SetColor(Color color)
{
	m_color = color;
}

Color CShape::GetColor() const
{
	return m_color;
}

CShape::CShape()
{
}


CShape::~CShape()
{
}
