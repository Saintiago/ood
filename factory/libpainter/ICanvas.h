#pragma once
#include <memory>
#include <string>

struct ICanvas
{
	virtual void SetColor(const Color) = 0;
	virtual void DrawLine(const Point & from, const Point &  to) = 0;
	virtual void DrawEllipse(const Point &  center, float width, float height) = 0;
	virtual ~ICanvas() = default;
};