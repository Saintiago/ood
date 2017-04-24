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

class CUtils
{
public:

	static std::string ImplodeViaSpace(Params params);
	static std::string ImplodeWithoutFirstElement(Params params);
	static Params ExplodeViaSpace(const std::string & description);
	static Color StringToColor(const std::string & colorStr);
	static std::string ColorToString(Color color);
	static void CUtils::CheckPoint(Point point);
	static void CUtils::CheckFloat(float fl);

private:
	CUtils() = default;

};

