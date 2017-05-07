#include "stdafx.h"
#include "../libpainter/Shape.h"
#include "../libpainter/Rectangle.h"
#include "../libpainter/RegularPolygon.h"
#include "../libpainter/ICanvas.h"
#include "../libpainter/Canvas.h"
#include <string>
#include <memory>
#include <iostream>
#include <sstream>

using namespace std;

class CMockCanvas : public ICanvas
{
public:
	string m_canvas = "";
	Color m_currentColor = Color::Black;

	void SetColor(const Color color) override
	{
		m_currentColor = color;
	}

	void DrawLine(const Point & from, const Point &  to) override
	{
		stringstream ss;
		ss << "Line "
			<< "[" << from.first << ", " << from.second << "], "
			<< "[" << to.first << ", " << to.second << "]"
			<< endl;
		m_canvas += ss.str();
	}

	void DrawEllipse(const Point &  center, float width, float height)
	{
		stringstream ss;
		ss << "Ellipse "
			<< "[" << center.first << ", " << center.second << "], "
			<< "width: " << width << ", height: " << height
			<< endl;
		m_canvas += ss.str();
	}
};

struct Shape_
{
	ShapePtr rectangle;
	CMockCanvas canvas;

	Shape_()
	{
		Color color = Color::Black;
		Point leftTop = { (float)0, (float)0 };
		Point rightBottom = { (float)1, (float)1 };
		rectangle = make_unique<CRectangle>(color, leftTop, rightBottom);
	}
};

BOOST_FIXTURE_TEST_SUITE(Shape, Shape_)
	BOOST_AUTO_TEST_CASE(can_convet_itself_to_string)
	{	
		string rectangleExpectedOutput = "rectangle black 0 0 1 1";
		BOOST_CHECK(rectangle->ToString() == rectangleExpectedOutput);
	}
	BOOST_AUTO_TEST_CASE(can_draw_itself)
	{
		stringstream rectangleExpectedOutput;
		rectangleExpectedOutput
			<< "Line [0, 0], [1, 0]" << endl
			<< "Line [1, 0], [1, 1]" << endl
			<< "Line [1, 1], [0, 1]" << endl
			<< "Line [0, 1], [0, 0]" << endl;

		rectangle->Draw(canvas);
		BOOST_CHECK_EQUAL(canvas.m_canvas, rectangleExpectedOutput.str());
	}
	BOOST_AUTO_TEST_CASE(polygon_can_draw_itself)
	{
		Color color = Color::Black;
		Point center = { (float)2, (float)2 };
		float radius = (float)1;
		int vertexCount = 3;
		CRegularPolygon polygon(color, center, radius, vertexCount);
		polygon.Draw(canvas);
		string expectedOutput = "Line [3, 2], [1.5, 2.86603]\nLine [1.5, 2.86603], [1.5, 1.13397]\nLine [1.5, 1.13397], [3, 2]\n";
		BOOST_CHECK_EQUAL(canvas.m_canvas, expectedOutput);
	}
BOOST_AUTO_TEST_SUITE_END()