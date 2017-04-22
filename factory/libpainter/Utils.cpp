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
	throw invalid_argument("Invalid color");
}

string CUtils::ColorToString(Color color)
{
	if (color == Color::Black) return "black";
	if (color == Color::Red) return "red";
	throw invalid_argument("Invalid color");
}