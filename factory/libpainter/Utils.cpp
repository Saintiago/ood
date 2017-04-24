#include "stdafx.h"
#include "Utils.h"
#include <utility>
#include <iostream>
#include <sstream>

#include <boost/algorithm/string/join.hpp>

using namespace std;

string CUtils::ImplodeViaSpace(Params params)
{
	return boost::algorithm::join(params, " ");
}

string CUtils::ImplodeWithoutFirstElement(Params params)
{
	params[0].erase();
	return ImplodeViaSpace(params);
}

Params CUtils::ExplodeViaSpace(const string & description)
{
	stringstream ss(description);
	Params params;
	string param;
	while (ss >> param)
	{
		params.push_back(param);
	}

	return params;
}

Color CUtils::StringToColor(const string & colorStr)
{
	if (colorStr == "black") return Color::Black;
	if (colorStr == "red") return Color::Red;
	if (colorStr == "green") return Color::Green;
	if (colorStr == "blue") return Color::Blue;
	if (colorStr == "pink") return Color::Pink;
	if (colorStr == "yellow") return Color::Yellow;
	throw invalid_argument("Invalid color");
}

string CUtils::ColorToString(Color color)
{
	if (color == Color::Black) return "black";
	if (color == Color::Red) return "red";
	if (color == Color::Green) return "green";
	if (color == Color::Blue) return "blue";
	if (color == Color::Pink) return "pink";
	if (color == Color::Yellow) return "yellow";
	throw invalid_argument("Invalid color");
}

void CUtils::CheckPoint(Point point)
{
	CUtils::CheckFloat(point.first);
	CUtils::CheckFloat(point.second);

}

void CUtils::CheckFloat(float fl)
{
	if (fl < 0)
	{
		throw invalid_argument("Params must not be lesser than zero");
	}
}