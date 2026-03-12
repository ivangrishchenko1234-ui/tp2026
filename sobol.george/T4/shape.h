#ifndef SHAPE
#define SHAPE
#include <iostream>
#include <cstdlib>
#include "point.h"

class Shape
{
public:
	virtual ~Shape() = default;
	virtual double getArea() const = 0;
	virtual Point getCenter() const = 0;
	virtual std::string getName() const = 0;
	virtual void move(const double& factorX, const double& factorY) = 0;
	virtual void scale(const double& factor) = 0;
	virtual void putInComposite(std::unique_ptr<Shape> shape)
	{
		if (getName() != "COMPOSITE")  return;
	}
	virtual void printInfoComposite()
	{
		if (getName() != "COMPOSITE")  return;
	}
};
#endif