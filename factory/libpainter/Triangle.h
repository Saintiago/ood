#pragma once
#include "Shape.h"
#include "ICanvas.h"

class CTriangle :
	public CShape
{
public:
	CTriangle(const std::string & description);
	~CTriangle();

	Point GetVertex1();
	Point GetVertex2();
	Point GetVertex3();

	virtual std::string ToString() override;
	virtual void Draw(ICanvas &) override;

private:
	void SetVertex1(Point);
	void SetVertex2(Point);
	void SetVertex3(Point);

	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};

