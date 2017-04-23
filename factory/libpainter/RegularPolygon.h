#pragma once
#include "Shape.h"
#include "ICanvas.h"

class CRegularPolygon :
	public CShape
{
public:
	CRegularPolygon(const std::string & description);
	~CRegularPolygon();

	Point GetCenter();
	float GetRadius();
	unsigned GetVertexCount();

	virtual std::string ToString() override;
	virtual void Draw(ICanvas &) override;

private:
	void SetCenter(Point);
	void SetRadius(float);
	void SetVertexCount(unsigned);

	std::vector<Point> GetPolygonVertieces();

	Point m_center;
	float m_radius;
	unsigned m_vertexCount;
};

