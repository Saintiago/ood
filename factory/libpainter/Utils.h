#pragma once
#include <vector>
#include <string>

using Params = std::vector<std::string>;
using Point = std::pair<float, float>;

enum class Color
{
	Black,
	Red,
	Green,
	Blue,
	Pink,
	Yellow
};

namespace utils
{
	std::string ImplodeViaSpace(Params params);
	std::string ImplodeWithoutFirstElement(Params params);
	Params ExplodeViaSpace(const std::string & description);
	Color StringToColor(const std::string & colorStr);
	std::string ColorToString(Color color);
	void CheckPoint(Point point);
	void CheckFloat(float fl);
}

