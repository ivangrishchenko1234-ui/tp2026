#ifndef ELLIPSE
#define ELLIPSE
#include <iostream>
#include <cstdlib>
#include "shape.h"

class Ellipse : public Shape
{
protected:
	Point center;
	double radiusX;
	double radiusY;
public:
	Ellipse(const Point& c, double rX, double rY) : center(c), radiusX(rX), radiusY(rY) {}
	~Ellipse() override
	{
		center.~Point();
	}
	double getArea() const override
	{
		return 3.14159 * radiusX * radiusY;
	}
	Point getCenter() const override
	{
		return center;
	}
	std::string getName() const override { return "ELLIPSE"; }
	void move(const double& factorX, const double& factorY) override
	{
		center.x += factorX;
		center.y += factorY;
	}
	void scale(const double& factor) override
	{
		radiusX *= factor;
		radiusY *= factor;
	}
};

#endif
