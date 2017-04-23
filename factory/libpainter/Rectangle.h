#pragma once
#include "Shape.h"
#include "ICanvas.h"

class CRectangle :
	public CShape
{
public:
	CRectangle(const std::string & description);
	~CRectangle();

	virtual std::string ToString() override;
	virtual void Draw(ICanvas &) override;

private:
	Point GetLeftTop();
	Point GetRightBottom();

	void SetLeftTop(Point);
	void SetRightBottom(Point);

	Point m_leftTop;
	Point m_rightBottom;
};

