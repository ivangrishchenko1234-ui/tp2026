#include "rectangle.h"

Rectangle::Rectangle(Point leftBottom, Point rightTop)
{

	center_ = { (leftBottom.x + rightTop.x) / 2, (leftBottom.y + rightTop.y) / 2 };
	height_ = (rightTop.y - leftBottom.y);
	width_ = (rightTop.x - leftBottom.x);
	if (height_ <= 0 || width_ <=0) {
		throw std::invalid_argument("Rectangle: height and width are supposed to be greater than zero");
	}
}

double Rectangle::getArea() const
{
	return (height_ * width_);
}

Point Rectangle::getCenter() const
{
	return center_;
}

void Rectangle::move(double dx, double dy)
{
	center_ = { (center_.x + dx), (center_.y + dy) };
}

void Rectangle::scale(double coeff)
{
	if (coeff <= 0) {
		throw std::invalid_argument("Rectangle (scale): coefficient can't be less than zero");
	}
	height_ *= coeff;
	width_ *= coeff;
}

std::string Rectangle::getName() const
{
	return "RECTANGLE";
}

RectanglePoints Rectangle::getBorderRectangle() const
{
	return { {center_.x - width_/2, center_.y - height_/2} ,  {center_.x + width_ / 2, center_.y + height_ / 2 } };
}

