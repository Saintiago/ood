#pragma once
#include "stdafx.h"
#include "ShapeFactory.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"
#include <memory>
#include <string>

using namespace std;
using namespace utils;

CShapeFactory::CShapeFactory()
{
}


CShapeFactory::~CShapeFactory()
{
}

ShapePtr CShapeFactory::CreateShape(const std::string & description)
{
	Params params = ExplodeViaSpace(description);
	string shapeType = params[0];

	if (shapeType == "rectangle")
	{
		Color color = StringToColor(params[1]);
		Point leftTop = { stof(params.at(2)), stof(params.at(3)) };
		Point rightBottom = { stof(params.at(4)), stof(params.at(5)) };
		return make_unique<CRectangle>(color, leftTop, rightBottom);
	}
	if (shapeType == "triangle")
	{
		Color color = StringToColor(params[1]);
		Point vertex1 = { stof(params.at(2)), stof(params.at(3)) };
		Point vertex2 = { stof(params.at(4)), stof(params.at(5)) };
		Point vertex3 = { stof(params.at(6)), stof(params.at(7)) };
		return make_unique<CTriangle>(color, vertex1, vertex2, vertex3);
	}
	if (shapeType == "ellipse")
	{
		Color color = StringToColor(params[1]);
		Point center = { stof(params.at(2)), stof(params.at(3)) };
		float horizontalRadius = stof(params.at(4));
		float verticalRadius = stof(params.at(5));
		return make_unique<CEllipse>(color, center, horizontalRadius, verticalRadius);
	}
	if (shapeType == "polygon")
	{
		Color color = StringToColor(params[1]);
		Point center = { stof(params.at(2)), stof(params.at(3)) };
		float radius = stof(params.at(4));
		int vertexCount = stoi(params.at(5));
		return make_unique<CRegularPolygon>(color, center, radius, vertexCount);
	}

	throw invalid_argument("Unknown shape type");
}