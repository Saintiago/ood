#include "stdafx.h"
#include "Painter.h"

void CPainter::DrawPicture(const CPictureDraft & draft, ICanvas & canvas)
{
	for (auto it = draft.begin(); it < draft.end(); it++)
	{
		it->Draw(canvas);
	}
}

CPainter::CPainter()
{
}


CPainter::~CPainter()
{
}
