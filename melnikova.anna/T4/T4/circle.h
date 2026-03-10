#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"


class Circle : public Shape {
private:
	Point center_;
	double radius_;
public:
	Circle(Point center, double radius);
	double getArea() const override;
	Point getCenter() const override;
	void move(double dx, double dy) override;
	void scale(double coeff) override;
	std::string getName() const override;
	RectanglePoints getBorderRectangle() const override;

};

#endif
