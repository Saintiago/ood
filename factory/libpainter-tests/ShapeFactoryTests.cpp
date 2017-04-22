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
	BOOST_AUTO_TEST_CASE(can_make_shape_by_string_input)
	{
		ShapePtr rectangle = factory.CreateShape("rectangle black 0 0 1 1");
		string rectangleExpectedOutput = "rectangle black 0 0 1 1";
		BOOST_CHECK_EQUAL(rectangle->ToString(), rectangleExpectedOutput);
	}
BOOST_AUTO_TEST_SUITE_END()