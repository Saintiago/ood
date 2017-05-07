#pragma once
#include "Shape.h"
#include "ICanvas.h"

class CRectangle :
	public CShape
{
public:
	CRectangle(Color, Point, Point);
	~CRectangle();

	virtual std::string ToString() const override;
	virtual void Draw(ICanvas &) const override;

private:
	Point GetLeftTop() const;
	Point GetRightBottom() const;

	void SetLeftTop(Point);
	void SetRightBottom(Point);

	Point m_leftTop;
	Point m_rightBottom;
};

