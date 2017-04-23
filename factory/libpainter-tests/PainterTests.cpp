#include "stdafx.h"
#include "../libpainter/Painter.h"
#include "../libpainter/Designer.h"
#include "../libpainter/Canvas.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/PictureDraft.h"
#include <string>
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

struct Painter_
{
	CPainter painter;
	CPictureDraft draft;
	CMockCanvas canvas;

	Painter_()
	{
		CShapeFactory factory;
		CDesigner designer(factory);

		stringstream input("rectangle black 0 0 1 1\ntriangle red 1 0 2 1 0 1\nellipse red 2 2 1 2\npolygon black 2 2 1 3");

		draft = designer.CreateDraft(input);
	}
};

BOOST_FIXTURE_TEST_SUITE(Painter, Painter_)
	BOOST_AUTO_TEST_CASE(can_draw_picture_by_draft_on_canvas)
	{
		painter.DrawPicture(draft, canvas);
		stringstream expectedCanvas;
		expectedCanvas
			<< "Line [0, 0], [1, 0]" << endl
			<< "Line [1, 0], [1, 1]" << endl
			<< "Line [1, 1], [0, 1]" << endl
			<< "Line [0, 1], [0, 0]" << endl

			<< "Line [1, 0], [2, 1]" << endl
			<< "Line [2, 1], [0, 1]" << endl
			<< "Line [0, 1], [1, 0]" << endl

			<< "Ellipse [2, 2], width: 1, height: 2" << endl

			<< "Line [3, 2], [1.5, 2.86603]" << endl
			<< "Line [1.5, 2.86603], [1.5, 1.13397]" << endl
			<< "Line [1.5, 1.13397], [3, 2]" << endl;

		BOOST_CHECK_EQUAL(canvas.m_canvas, expectedCanvas.str());
	}		
BOOST_AUTO_TEST_SUITE_END()