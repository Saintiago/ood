#pragma once
#include "stdafx.h"
#include "Triangle.h"
#include "Canvas.h"
#include <iostream>
#include <sstream>

using namespace std;

std::string CTriangle::ToString()
{
	stringstream ss;
	Point v1 = GetVertex1();
	Point v2 = GetVertex2();
	Point v3 = GetVertex3();
	string color = CUtils::ColorToString(GetColor());
	ss << "triangle " << color << " "
		<< v1.first << " " << v1.second << " "
		<< v2.first << " " << v2.second << " "
		<< v3.first << " " << v3.second;
	return ss.str();
}

void CTriangle::Draw(ICanvas & canvas)
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}

Point CTriangle::GetVertex1()
{
	return m_vertex1;
}
Point CTriangle::GetVertex2()
{
	return m_vertex2;
}
Point CTriangle::GetVertex3()
{
	return m_vertex3;
}

void CTriangle::SetVertex1(Point vertex)
{
	m_vertex1 = vertex;
}
void CTriangle::SetVertex2(Point vertex)
{
	m_vertex2 = vertex;
}
void CTriangle::SetVertex3(Point vertex)
{
	m_vertex3 = vertex;
}

CTriangle::CTriangle(const std::string & description)
{
	Params params = CUtils::ExplodeViaSpace(description);

	SetColor(CUtils::StringToColor(params.at(0)));
	SetVertex1({ stof(params.at(1)), stof(params.at(2)) });
	SetVertex2({ stof(params.at(3)), stof(params.at(4)) });
	SetVertex3({ stof(params.at(5)), stof(params.at(6)) });
}


CTriangle::~CTriangle()
{
}
