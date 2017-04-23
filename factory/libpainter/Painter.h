#pragma once
#include "IPainter.h"

class CPainter : IPainter
{
public:

	virtual void DrawPicture(const CPictureDraft &, ICanvas &) override;

	CPainter();
	~CPainter();
};

