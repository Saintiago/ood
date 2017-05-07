#pragma once
#include "stdafx.h"
#include "Triangle.h"
#include "Canvas.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace utils;

std::string CTriangle::ToString() const
{
	stringstream ss;
	Point v1 = GetVertex1();
	Point v2 = GetVertex2();
	Point v3 = GetVertex3();
	string color = ColorToString(GetColor());
	ss << "triangle " << color << " "
		<< v1.first << " " << v1.second << " "
		<< v2.first << " " << v2.second << " "
		<< v3.first << " " << v3.second;
	return ss.str();
}

void CTriangle::Draw(ICanvas & canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}

Point CTriangle::GetVertex1() const
{
	return m_vertex1;
}
Point CTriangle::GetVertex2() const
{
	return m_vertex2;
}
Point CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::SetVertex1(Point vertex)
{
	CheckPoint(vertex);
	m_vertex1 = vertex;
}
void CTriangle::SetVertex2(Point vertex)
{
	CheckPoint(vertex);
	m_vertex2 = vertex;
}
void CTriangle::SetVertex3(Point vertex)
{
	CheckPoint(vertex);
	m_vertex3 = vertex;
}

CTriangle::CTriangle(Color color, Point vertex1, Point vertex2, Point vertex3)
	: CShape(color)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}


CTriangle::~CTriangle()
{
}