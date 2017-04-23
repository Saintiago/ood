#pragma once
#include "stdafx.h"
#include "ICanvas.h"

class CSvgCanvas :
	public ICanvas
{
public:
	CSvgCanvas();
	~CSvgCanvas();

	void SetColor(const Color color) override;
	void DrawLine(const Point & from, const Point &  to) override;
	void DrawEllipse(const Point &  center, float width, float height) override;

private:
	const std::string m_header = "<html><body><svg width=\"200\" height=\"200\">";
	const std::string m_footer = "</svg></body></html>";

	Color m_currentColor;
	std::string m_canvas;

	void StoreCanvas();
	std::string ColorToRGB(Color);
};

