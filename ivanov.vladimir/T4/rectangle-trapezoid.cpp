#include "rectangle-trapezoid.h"
#include <stdexcept>

RectangleTrapezoid::RectangleTrapezoid(const Point &bottomLeft, double bottomWidth,
                                       double topWidth, double height) : bottomLeft_(bottomLeft),
                                                                         bottomWidth_(bottomWidth),
                                                                         topWidth_(topWidth),
                                                                         height_(height) {
    if (bottomWidth <= 0.0 || topWidth <= 0.0 || height <= 0.0) {
        throw std::invalid_argument("Trapezoid dimensions must be positive");
    }
}

double RectangleTrapezoid::getArea() const {
    return ((bottomWidth_ + topWidth_) / 2.0) * height_;
}

Point RectangleTrapezoid::getCenter() const {
    double cx = bottomLeft_.x + (bottomWidth_ + topWidth_) / 4.0;
    double cy = bottomLeft_.y + height_ / 2.0;
    return {cx, cy};
}

void RectangleTrapezoid::move(double dx, double dy) {
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;
}

void RectangleTrapezoid::move(const Point &newCenter) {
    Point current = getCenter();
    move(newCenter.x - current.x, newCenter.y - current.y);
}

void RectangleTrapezoid::scale(double factor) {
    if (factor <= 0.0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    Point c = getCenter();
    bottomWidth_ *= factor;
    topWidth_ *= factor;
    height_ *= factor;
    bottomLeft_.x = c.x - (bottomWidth_ + topWidth_) / 4.0;
    bottomLeft_.y = c.y - height_ / 2.0;
}

std::string RectangleTrapezoid::getName() const {
    return "RECTANGLE_TRAPEZOID";
}
