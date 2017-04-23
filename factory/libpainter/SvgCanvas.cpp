#include "stdafx.h"
#include "SvgCanvas.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

CSvgCanvas::CSvgCanvas()
{
}


CSvgCanvas::~CSvgCanvas()
{
}

void CSvgCanvas::SetColor(const Color color)
{
	m_currentColor = color;
}

void CSvgCanvas::DrawLine(const Point & from, const Point &  to)
{
	//<line x1="0" y1="0" x2="200" y2="200" style="stroke:rgb(255,0,0);stroke-width:2" />
	stringstream ss;
	ss << "<line "
		<< "x1=\"" << from.first << "\" y1=\"" << from.second << "\" "
		<< "x2=\"" << to.first << "\" y2=\"" << to.second << "\" "
		<< "style=\"stroke:" << ColorToRGB(m_currentColor) << ";stroke - width:2\" "
		<< "/>";
	m_canvas += ss.str();
	StoreCanvas();
}

void CSvgCanvas::DrawEllipse(const Point &  center, float width, float height)
{
	//<ellipse cx="200" cy="80" rx="100" ry="50"
    //style = "fill:yellow;stroke:purple;stroke-width:2" / >
	stringstream ss;
	ss << "<ellipse "
		<< "cx = \"" << center.first << "\" cy = \"" << center.second << "\" "
		<< "rx = \"" << width << "\" ry = \"" << height << "\" "
		<< "style = \"fill:white;stroke:" << ColorToRGB(m_currentColor) << ";stroke-width:2\" "
		<< "/>";
	m_canvas += ss.str();
	StoreCanvas();
}

void CSvgCanvas::StoreCanvas()
{
	ofstream canvasFile("svg_canvas.html", std::ios_base::out);
	canvasFile << m_header << m_canvas << m_footer;
}

string CSvgCanvas::ColorToRGB(Color color)
{
	if (color == Color::Black) return "rgb(0, 0, 0)";
	if (color == Color::Red) return "rgb(255, 0, 0)";
	if (color == Color::Green) return "rgb(0, 255, 0)";
	if (color == Color::Blue) return "rgb(0, 0, 255)";
	if (color == Color::Pink) return "rgb(255,192,203)";
	if (color == Color::Yellow) return "rgb(255, 255, 0)";
	throw invalid_argument("Invalid color");
}