#pragma once
#include "stdafx.h"
#include "Rectangle.h"
#include "Canvas.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace utils;

std::string CRectangle::ToString() const
{
	stringstream ss;
	Point lt = GetLeftTop();
	Point rb = GetRightBottom();
	string color = ColorToString(GetColor());
	ss << "rectangle " << color << " " << lt.first << " " << lt.second << " " << rb.first << " " << rb.second;
	return ss.str();
}

void CRectangle::Draw(ICanvas & canvas) const
{
	Point p1 = m_leftTop;
	Point p2 = { m_rightBottom.first, m_leftTop.second };
	Point p3 = m_rightBottom;
	Point p4 = { m_leftTop.first, m_rightBottom.second };

	canvas.SetColor(GetColor());
	canvas.DrawLine(p1, p2);
	canvas.DrawLine(p2, p3);
	canvas.DrawLine(p3, p4);
	canvas.DrawLine(p4, p1);
}

Point CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

void CRectangle::SetLeftTop(Point leftTop)
{
	CheckPoint(leftTop);
	m_leftTop = leftTop;
}

void CRectangle::SetRightBottom(Point rightBottom)
{
	CheckPoint(rightBottom);
	m_rightBottom = rightBottom;
}

CRectangle::CRectangle(Color color, Point leftTop, Point rightBottom)
	: CShape(color)
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	
{
}


CRectangle::~CRectangle()
{
}
