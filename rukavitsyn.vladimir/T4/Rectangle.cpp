#include "Rectangle.h"
#include <algorithm>
#include <stdexcept>

Rectangle::Rectangle(const Point& bl, const Point& tr) {
    if (bl.x_ >= tr.x_ || bl.y_ >= tr.y_) {
        throw std::invalid_argument("Error: Invalid rectangle coordinates. ");
    }
    bottomLeft_ = bl;
    topRight_ = tr;
}

double Rectangle::getArea() const {
    double width = topRight_.x_ - bottomLeft_.x_;
    double height = topRight_.y_ - bottomLeft_.y_;
    return width * height;
}

Point Rectangle::getCenter() const {
    return Point((bottomLeft_.x_ + topRight_.x_) / 2.0,
        (bottomLeft_.y_ + topRight_.y_) / 2.0);
}

void Rectangle::move(double dx, double dy) {
    bottomLeft_.x_ += dx;
    bottomLeft_.y_ += dy;
    topRight_.x_ += dx;
    topRight_.y_ += dy;
}

void Rectangle::scale(double factor) {
    Point center = getCenter();
    double dxBL = bottomLeft_.x_ - center.x_;
    double dyBL = bottomLeft_.y_ - center.y_;
    double dxTR = topRight_.x_ - center.x_;
    double dyTR = topRight_.y_ - center.y_;

    bottomLeft_.x_ = center.x_ + dxBL * factor;
    bottomLeft_.y_ = center.y_ + dyBL * factor;
    topRight_.x_ = center.x_ + dxTR * factor;
    topRight_.y_ = center.y_ + dyTR * factor;
}

std::string Rectangle::getName() const {
    return "Rectangle";
}

std::pair<Point, Point> Rectangle::circumscribedRectangle() const {
    return { bottomLeft_, topRight_ };
}

void Rectangle::print(std::ostream& stream) const {
    stream << getName() << ", Center = (" << getCenter().x_ << ", " << getCenter().y_ << "), ";
    stream << "Area = " << getArea() << ";\n";
}
