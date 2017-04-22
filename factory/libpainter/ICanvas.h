#pragma once
#include <memory>
#include <string>

class CShape;

struct ICanvas
{
	virtual void SetColor(const Color) = 0;
	virtual void DrawLine(const Point & from, const Point &  to) = 0;
	virtual void DrawEllipse(const Point &  left, const Point &  top, int width, int height) = 0;
	virtual ~ICanvas() = default;
};