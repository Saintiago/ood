#pragma once
#include <memory>
#include "Canvas.h"

struct IShape
{
	virtual std::string ToString() = 0;
	virtual void Draw(ICanvas &) = 0;
	virtual ~IShape() = default;
};
