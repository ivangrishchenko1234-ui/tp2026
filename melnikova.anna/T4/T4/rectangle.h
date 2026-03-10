#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle: public Shape {
private:
	Point center_;
	double height_;
	double width_;
public:
	Rectangle(Point leftBottom, Point rightTop);
	double getArea() const override;
	Point getCenter() const override;
	void move(double dx, double dy) override;
	void scale(double coeff) override;
	std::string getName() const override;
	RectanglePoints getBorderRectangle() const override;

};

#endif
