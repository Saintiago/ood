#include "stdafx.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/IShape.h"
#include <string>

using namespace std;

struct ShapeFactory_
{
	CShapeFactory factory;
};

BOOST_FIXTURE_TEST_SUITE(ShapeFactory, ShapeFactory_)
	BOOST_AUTO_TEST_CASE(can_make_rectangle_by_string_input)
	{
		ShapePtr rectangle = factory.CreateShape("rectangle black 0 0 1 1");
		string rectangleExpectedOutput = "rectangle black 0 0 1 1";
		BOOST_CHECK_EQUAL(rectangle->ToString(), rectangleExpectedOutput);
	}
	BOOST_AUTO_TEST_CASE(can_make_triangle_by_string_input)
	{
		ShapePtr triangle = factory.CreateShape("triangle red 1 0 2 1 0 1");
		string triangleExpectedOutput = "triangle red 1 0 2 1 0 1";
		BOOST_CHECK_EQUAL(triangle->ToString(), triangleExpectedOutput);
	}
	BOOST_AUTO_TEST_CASE(can_make_ellipse_by_string_input)
	{
		ShapePtr triangle = factory.CreateShape("ellipse red 2 2 1 2");
		string triangleExpectedOutput = "ellipse red 2 2 1 2";
		BOOST_CHECK_EQUAL(triangle->ToString(), triangleExpectedOutput);
	}
	BOOST_AUTO_TEST_CASE(can_make_polygon_by_string_input)
	{
		ShapePtr polygon = factory.CreateShape("polygon black 1 1 1 4");
		string polygonExpectedOutput = "polygon black 1 1 1 4";
		BOOST_CHECK_EQUAL(polygon->ToString(), polygonExpectedOutput);
	}
BOOST_AUTO_TEST_SUITE_END()