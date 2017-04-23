#pragma once
#include "Shape.h"
#include "ICanvas.h"

class CEllipse :
	public CShape
{
public:
	CEllipse(const std::string & description);
	~CEllipse();

	Point GetCenter() const;
	float GetHorizontalRadius() const;
	float GetVerticalRadius() const;

	virtual std::string ToString() const override;
	virtual void Draw(ICanvas &) const override;

private:
	void SetCenter(Point);
	void SetHorizontalRadius(float);
	void SetVerticalRadius(float);

	Point m_center;
	float m_horizontalRadius;
	float m_verticalRadius;
};

