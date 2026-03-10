#include "isosceles_trapezoid.h"

IsoscelesTrapezoid::IsoscelesTrapezoid(Point leftBottom, double baseBottom, double baseTop, double height) :
	height_(height), baseTop_(baseTop), baseBottom_(baseBottom)
{
	if (height_ <= 0 || baseTop <= 0 || baseBottom <= 0) {
		throw std::invalid_argument("Isosceles Trapezoid: height and bases are supposed to be greater than zero");
	}
	center_ = { (leftBottom.x + baseBottom_ / 2), (leftBottom.y + height_ / 2) };
}

double IsoscelesTrapezoid::getArea() const
{
	return ((baseTop_ + baseBottom_) / 2 * height_);
}

Point IsoscelesTrapezoid::getCenter() const
{
	return center_;
}

void IsoscelesTrapezoid::move(double dx, double dy)
{
	center_ = { (center_.x + dx),(center_.y + dy) };
}

void IsoscelesTrapezoid::scale(double coeff)
{
	if (coeff <= 0) {
		throw std::invalid_argument("Isosceles Trapezoid (scale): coefficient can't be less than zero");
	}
	height_ *= coeff;
	baseTop_ *= coeff;
	baseBottom_ *= coeff;
}

std::string IsoscelesTrapezoid::getName() const
{
	return "ISOSCELES TRAPEZOID";
}

RectanglePoints IsoscelesTrapezoid::getBorderRectangle() const
{
	double maxBase = std::max(baseBottom_, baseTop_);

	return {
		{center_.x - maxBase / 2.0, center_.y - height_ / 2.0},
		{center_.x + maxBase / 2.0, center_.y + height_ / 2.0}
	};
}

