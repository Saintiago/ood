#include "stdafx.h"
#include "Canvas.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

CCanvas::CCanvas()
{
}


CCanvas::~CCanvas()
{
}

void CCanvas::SetColor(const Color color)
{
	m_currentColor = color;
}

void CCanvas::DrawLine(const Point & from, const Point &  to)
{
	stringstream ss;
	ss << "Line "
		<< "[" << from.first << ", " << from.second << "], "
		<< "[" << to.first << ", " << to.second << "]"
		<< endl;
	m_canvas += ss.str();
}

void CCanvas::DrawEllipse(const Point &  left, const Point &  top, int width, int height)
{
	stringstream ss;
	ss << "Ellipse "
		<< "[" << left.first << ", " << left.second << "], "
		<< "[" << top.first << ", " << top.second << "], "
		<< "width: " << width << ", height: " << height
		<< endl;
	m_canvas += ss.str();
}
