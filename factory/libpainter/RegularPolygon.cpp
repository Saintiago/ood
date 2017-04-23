#pragma once
#include "stdafx.h"
#include "RegularPolygon.h"
#include "Canvas.h"
#include <iostream>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace std;

std::string CRegularPolygon::ToString() const
{
	stringstream ss;
	Point c = GetCenter();
	float radius = GetRadius();
	unsigned vertiecesCount = GetVertexCount();
	string color = CUtils::ColorToString(GetColor());
	ss << "polygon " << color << " "
		<< c.first << " " << c.second << " "
		<< radius << " " << vertiecesCount;
	return ss.str();
}

void CRegularPolygon::Draw(ICanvas & canvas) const
{
	canvas.SetColor(GetColor());
	
	vector<Point> verticies = GetPolygonVertieces();

	for (unsigned i = 0; i < (verticies.size() - 1); ++i)
	{
		canvas.DrawLine(verticies.at(i), verticies.at(i + 1));
	}
	canvas.DrawLine(verticies.at(verticies.size() - 1), verticies.at(0));
}

Point CRegularPolygon::GetCenter() const
{
	return m_center;
}
float CRegularPolygon::GetRadius() const
{
	return m_radius;
}
unsigned CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

void CRegularPolygon::SetCenter(Point point)
{
	m_center = point;
}
void CRegularPolygon::SetRadius(float radius)
{
	if (radius == 0)
	{
		throw invalid_argument("Radius must be bigger than 0");
	}
	m_radius = radius;
}
void CRegularPolygon::SetVertexCount(unsigned vertexCount)
{
	if (vertexCount < 3)
	{
		throw invalid_argument("There must be at least 3 verticies in polygon");
	}
	m_vertexCount = vertexCount;
}

std::vector<Point> CRegularPolygon::GetPolygonVertieces() const
{
	vector<Point> polygonVertieces;
	const float step = float(2 * M_PI / m_vertexCount);
	for (float angle = 0; angle < float(2 * M_PI); angle += step)
	{
		const float dx = m_radius * cosf(angle);
		const float dy = m_radius * sinf(angle);
		polygonVertieces.push_back({ dx + m_center.first, dy + m_center.second });
	}
	return polygonVertieces;
}

CRegularPolygon::CRegularPolygon(const std::string & description)
{
	Params params = CUtils::ExplodeViaSpace(description);

	SetColor(CUtils::StringToColor(params.at(0)));
	SetCenter({ stof(params.at(1)), stof(params.at(2)) });
	SetRadius(stof(params.at(3)));
	SetVertexCount(stoi(params.at(4)));
}


CRegularPolygon::~CRegularPolygon()
{
}
