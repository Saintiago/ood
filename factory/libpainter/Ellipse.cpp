#pragma once
#include "stdafx.h"
#include "Ellipse.h"
#include "Canvas.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace utils;

std::string CEllipse::ToString() const
{
	stringstream ss;
	Point c = GetCenter();
	float hr = GetHorizontalRadius();
	float vr = GetVerticalRadius();
	string color = ColorToString(GetColor());
	ss << "ellipse " << color << " "
		<< c.first << " " << c.second << " "
		<< hr << " " << vr;
	return ss.str();
}

void CEllipse::Draw(ICanvas & canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}

Point CEllipse::GetCenter() const
{
	return m_center;
}
float CEllipse::GetHorizontalRadius() const
{
	return m_horizontalRadius;
}
float CEllipse::GetVerticalRadius() const
{
	return m_verticalRadius;
}

void CEllipse::SetCenter(Point point)
{
	CheckPoint(point);
	m_center = point;
}
void CEllipse::SetHorizontalRadius(float width)
{
	CheckFloat(width);
	m_horizontalRadius = width;
}
void CEllipse::SetVerticalRadius(float height)
{
	CheckFloat(height);
	m_verticalRadius = height;
}

CEllipse::CEllipse(Color color, Point center, float horizontalRadius, float verticalRadius)
	: CShape(color)
	, m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}


CEllipse::~CEllipse()
{
}
