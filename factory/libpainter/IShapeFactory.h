#pragma once
#include <memory>
#include <string>
#include "Shape.h"

struct IShapeFactory
{
	virtual ShapePtr CreateShape(const std::string & description) = 0;

	virtual ~IShapeFactory() = default;
};