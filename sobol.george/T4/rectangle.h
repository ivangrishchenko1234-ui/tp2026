#ifndef RECT
#define RECT
#include <iostream>
#include <cstdlib>
#include "shape.h"

class Rectangle : public Shape
{
protected:
	Point botLet;
	Point topRit;
public:
	Rectangle(const Point& bl, const Point& tr) : botLet(bl), topRit(tr) {}
	Rectangle(const double& blX, const double& blY, const double& trX, const double& trY)
	{
		botLet.x = blX;
		botLet.y = blY;
		topRit.x = trX;
		topRit.y = trY;
	}
	~Rectangle() override
	{
		botLet.~Point();
		topRit.~Point();
	}

	double getArea() const override
	{
		double width = topRit.x - botLet.x;
		double height = topRit.y - botLet.y;
		return std::abs(width * height);
	}
	Point getCenter() const override
	{
		double centerX = (botLet.x + topRit.x) / 2.0;
		double centerY = (botLet.y + topRit.y) / 2.0;
		return Point(centerX, centerY);
	}
	std::string getName() const override { return "RECTANGLE"; }
	void move(const double& factorX, const double& factorY) override
	{
		botLet.x += factorX;
		topRit.x += factorX;
		botLet.y += factorY;
		topRit.y += factorY;
	}
	void scale(const double& factor) override
	{
		Point center = this->getCenter();
		botLet.x = center.x + (botLet.x - center.x) * factor;
		botLet.y = center.y + (botLet.y - center.y) * factor;
		topRit.x = center.x + (topRit.x - center.x) * factor;
		topRit.y = center.y + (topRit.y - center.y) * factor;
	}
};

#endif