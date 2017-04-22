#pragma once
#include <memory>
#include "Canvas.h"
#include "IShape.h"

class CShape : IShape
{
public:
	virtual std::string ToString();
	virtual void Draw(ICanvas &);

	void SetColor(Color);
	Color GetColor();

	CShape();
	virtual ~CShape();

private:
	Color m_color;
};

using ShapePtr = std::unique_ptr<CShape>;
