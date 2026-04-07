#include "Square.h"

Point Square::getCenter() const {
    return Point(bottomLeft_.x_ + length_ / 2.0,
        bottomLeft_.y_ + length_ / 2.0);
}

void Square::move(double dx, double dy) {
    bottomLeft_.x_ += dx;
    bottomLeft_.y_ += dy;
}

void Square::scale(double factor) {
    Point center = getCenter();
    bottomLeft_.x_ = center.x_ + (bottomLeft_.x_ - center.x_) * factor;
    bottomLeft_.y_ = center.y_ + (bottomLeft_.y_ - center.y_) * factor;
    length_ *= factor;
}

std::string Square::getName() const {
    return "Square";
}

std::pair<Point, Point> Square::circumscribedRectangle() const {
    return { bottomLeft_, Point(bottomLeft_.x_ + length_, bottomLeft_.y_ + length_) };
}

void Square::print(std::ostream& stream) const
{
    stream << getName() << ", Center = (" << getCenter().x_ << ", " << getCenter().y_ << "), ";
    stream << "Area = " << getArea();
    stream << " Length = " << length_ << ";\n";
}
