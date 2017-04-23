#include "stdafx.h"
#include "../libpainter/SvgCanvas.h"
#include "../libpainter/Painter.h"
#include "../libpainter/Designer.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/PictureDraft.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct SvgCanvas_
{
	CSvgCanvas canvas;
	CPainter painter;
	CPictureDraft draft;

	SvgCanvas_()
	{
		CShapeFactory factory;
		CDesigner designer(factory);

		stringstream input("ellipse red 2 2 1 2");

		draft = designer.CreateDraft(input);
	}
};

BOOST_FIXTURE_TEST_SUITE(SvgCanvas, SvgCanvas_)
	BOOST_AUTO_TEST_CASE(can_render_itself_to_file)
	{
		painter.DrawPicture(draft, canvas);

		stringstream expectedFileContents("<html><body><svg width=\"200\" height=\"200\"><ellipse cx = \"2\" cy = \"2\" rx = \"1\" ry = \"2\" style = \"fill:white;stroke:rgb(255, 0, 0);stroke-width:2\" /></svg></body></html>");
		ifstream canvasFile("svg_canvas.html");
		string temp;
		stringstream realFileContents;
		while (std::getline(canvasFile, temp)) 
		{
			realFileContents << temp;
		}
		BOOST_CHECK_EQUAL(expectedFileContents.str(), realFileContents.str());
	}
BOOST_AUTO_TEST_SUITE_END()