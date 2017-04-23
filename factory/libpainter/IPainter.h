#pragma once
#include "PictureDraft.h"
#include "ICanvas.h"

struct IPainter
{
	virtual void DrawPicture(const CPictureDraft &, ICanvas &) = 0;
	virtual ~IPainter() = default;
};