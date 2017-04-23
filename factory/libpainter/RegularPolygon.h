#pragma once
#include "Shape.h"
#include "ICanvas.h"

class CRegularPolygon :
	public CShape
{
public:
	CRegularPolygon(const std::string & description);
	~CRegularPolygon();

	Point GetCenter() const;
	float GetRadius() const;
	unsigned GetVertexCount() const;

	virtual std::string ToString() const override;
	virtual void Draw(ICanvas &) const override;

private:
	void SetCenter(Point);
	void SetRadius(float);
	void SetVertexCount(unsigned);

	std::vector<Point> GetPolygonVertieces() const;

	Point m_center;
	float m_radius;
	unsigned m_vertexCount;
};

