#pragma once
#include <vector>
#include <string>

using Params = std::vector<std::string>;
using Point = std::pair<int, int>;
enum class Color
{
	Black,
	Red
};

class CUtils
{
public:

	static std::string ImplodeViaSpace(Params params);
	static std::string ImplodeWithoutFirstElement(Params params);
	static Params ExplodeViaSpace(const std::string & description);
	static Color StringToColor(const std::string & colorStr);
	static std::string ColorToString(Color color);

private:
	CUtils() = default;

};

