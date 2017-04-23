#pragma once
#include "Shape.h"
#include "ICanvas.h"

class CTriangle :
	public CShape
{
public:
	CTriangle(const std::string & description);
	~CTriangle();

	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

	virtual std::string ToString() const override;
	virtual void Draw(ICanvas &) const override;

private:
	void SetVertex1(Point);
	void SetVertex2(Point);
	void SetVertex3(Point);

	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};

