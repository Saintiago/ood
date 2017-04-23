#pragma once
#include "Shape.h"
#include "ICanvas.h"

class CEllipse :
	public CShape
{
public:
	CEllipse(const std::string & description);
	~CEllipse();

	Point GetCenter();
	float GetHorizontalRadius();
	float GetVerticalRadius();

	virtual std::string ToString() override;
	virtual void Draw(ICanvas &) override;

private:
	void SetCenter(Point);
	void SetHorizontalRadius(float);
	void SetVerticalRadius(float);

	Point m_center;
	float m_horizontalRadius;
	float m_verticalRadius;
};

