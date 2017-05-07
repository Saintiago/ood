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
	string shapeDescription = ImplodeWithoutFirstElement(params);

	if (shapeType == "rectangle")
	{
		return make_unique<CRectangle>(shapeDescription);
	}
	if (shapeType == "triangle")
	{
		return make_unique<CTriangle>(shapeDescription);
	}
	if (shapeType == "ellipse")
	{
		return make_unique<CEllipse>(shapeDescription);
	}
	if (shapeType == "polygon")
	{
		return make_unique<CRegularPolygon>(shapeDescription);
	}

	throw invalid_argument("Unknown shape type");
}