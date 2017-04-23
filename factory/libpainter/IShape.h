#pragma once
#include <memory>
#include "Canvas.h"

struct IShape
{
	virtual std::string ToString() const = 0;
	virtual void Draw(ICanvas &) const = 0;
	virtual ~IShape() = default;
};
