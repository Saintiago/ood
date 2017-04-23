#pragma once
#include <memory>
#include "Canvas.h"
#include "IShape.h"

class CShape : IShape
{
public:
	virtual std::string ToString() const override = 0;
	virtual void Draw(ICanvas &) const override = 0;

	void SetColor(Color);
	Color GetColor() const;

	CShape();
	virtual ~CShape();

private:
	Color m_color;
};

using ShapePtr = std::unique_ptr<CShape>;
