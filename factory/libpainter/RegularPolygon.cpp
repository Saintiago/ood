#pragma once
#include "stdafx.h"
#include "RegularPolygon.h"
#include "Canvas.h"
#include <iostream>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace std;
using namespace utils;

std::string CRegularPolygon::ToString() const
{
	stringstream ss;
	Point c = GetCenter();
	float radius = GetRadius();
	unsigned verticesCount = GetVertexCount();
	string color = ColorToString(GetColor());
	ss << "polygon " << color << " "
		<< c.first << " " << c.second << " "
		<< radius << " " << verticesCount;
	return ss.str();
}

void CRegularPolygon::Draw(ICanvas & canvas) const
{
	canvas.SetColor(GetColor());
	
	vector<Point> verticies = GetPolygonvertices();

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
	CheckPoint(point);
	m_center = point;
}
void CRegularPolygon::SetRadius(float radius)
{
	CheckFloat(radius);
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

std::vector<Point> CRegularPolygon::GetPolygonvertices() const
{
	vector<Point> polygonvertices;
	const float step = float(2 * M_PI / m_vertexCount);
	for (float angle = 0; angle < float(2 * M_PI); angle += step)
	{
		const float dx = m_radius * cosf(angle);
		const float dy = m_radius * sinf(angle);
		polygonvertices.push_back({ dx + m_center.first, dy + m_center.second });
	}
	return polygonvertices;
}

CRegularPolygon::CRegularPolygon(Color color, Point center, float radius, int vertexCount)
	: CShape(color)
	, m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
{
}


CRegularPolygon::~CRegularPolygon()
{
}
