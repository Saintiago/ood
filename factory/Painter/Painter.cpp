// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/SvgCanvas.h"
#include "../libpainter/Painter.h"
#include "../libpainter/Designer.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/PictureDraft.h"
#include <iostream>

using namespace std;

int main()
{
	try
	{
		CSvgCanvas canvas;
		CPainter painter;
		CPictureDraft draft;

		CShapeFactory factory;
		CDesigner designer(factory);

		fstream canvasFile("input.txt");
		draft = designer.CreateDraft(canvasFile);

		painter.DrawPicture(draft, canvas);
	}
	catch (const exception & e)
	{
		cerr << e.what() << endl;
		return 1;
	}

	return 0;
}

