#pragma once
#include "stdafx.h"
#include "Ellipse.h"
#include "Canvas.h"
#include <iostream>
#include <sstream>

using namespace std;

std::string CEllipse::ToString()
{
	stringstream ss;
	Point c = GetCenter();
	float hr = GetHorizontalRadius();
	float vr = GetVerticalRadius();
	string color = CUtils::ColorToString(GetColor());
	ss << "ellipse " << color << " "
		<< c.first << " " << c.second << " "
		<< hr << " " << vr;
	return ss.str();
}

void CEllipse::Draw(ICanvas & canvas)
{
	canvas.SetColor(GetColor());
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}

Point CEllipse::GetCenter()
{
	return m_center;
}
float CEllipse::GetHorizontalRadius()
{
	return m_horizontalRadius;
}
float CEllipse::GetVerticalRadius()
{
	return m_verticalRadius;
}

void CEllipse::SetCenter(Point point)
{
	m_center = point;
}
void CEllipse::SetHorizontalRadius(float width)
{
	if (width == 0)
	{
		throw invalid_argument("Horizontal radius must be bigger than 0");
	}
	m_horizontalRadius = width;
}
void CEllipse::SetVerticalRadius(float height)
{
	if (height == 0)
	{
		throw invalid_argument("Vertical radius must be bigger than 0");
	}
	m_verticalRadius = height;
}

CEllipse::CEllipse(const std::string & description)
{
	Params params = CUtils::ExplodeViaSpace(description);

	SetColor(CUtils::StringToColor(params.at(0)));
	SetCenter({ stof(params.at(1)), stof(params.at(2)) });
	SetHorizontalRadius(stof(params.at(3)));
	SetVerticalRadius(stof(params.at(4)));
}


CEllipse::~CEllipse()
{
}
