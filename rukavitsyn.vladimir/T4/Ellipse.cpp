#include "Ellipse.h"

double Ellipse::getArea() const {
    return PI * radX_ * radY_;
}

void Ellipse::move(double dx, double dy) {
    center_.x_ += dx;
    center_.y_ += dy;
}

void Ellipse::scale(double factor) {
    radX_ *= factor;
    radY_ *= factor;
}

std::string Ellipse::getName() const {
    return "Ellipse";
}

std::pair<Point, Point> Ellipse::circumscribedRectangle() const {
    return { Point(center_.x_ - radX_,center_.y_ - radY_), Point(center_.x_ + radX_,center_.y_ + radY_) };
}

void Ellipse::print(std::ostream& stream) const {
    stream << getName() << ", Center = (" << getCenter().x_ << ", " << getCenter().y_ << "), ";
    stream << "Area = " << getArea() << ";\n";
}
