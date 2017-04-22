#pragma once
#include "IShapeFactory.h"

class CShapeFactory :
	public IShapeFactory
{
public:
	CShapeFactory();
	~CShapeFactory();

	virtual ShapePtr CreateShape(const std::string & description) override;
};

