#pragma once
#include "stdafx.h"
#include "ShapeFactory.h"
#include "Rectangle.h"
#include <memory>
#include <string>

using namespace std;

CShapeFactory::CShapeFactory()
{
}


CShapeFactory::~CShapeFactory()
{
}

ShapePtr CShapeFactory::CreateShape(const std::string & description)
{
	Params params = CUtils::ExplodeViaSpace(description);
	string shapeType = params[0];
	
	if (shapeType == "rectangle")
	{
		string shapeDescription = CUtils::ImplodeWithoutFirstElement(params);
		return make_unique<CRectangle>(shapeDescription);
	}

	throw invalid_argument("Unknown shape type");
}