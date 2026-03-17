#include "circle.h"
#include <cmath>

Circle::Circle(const Point &center, double radius) : 
center_(center), radius_(radius) {
    if (radius <= 0.0) {
        throw std::invalid_argument("Radius must be positive");
    }
}

double Circle::getArea() const { return M_PI * radius_ * radius_; }

Point Circle::getCenter() const { return center_; }

void Circle::move(double dx, double dy) {
  center_.x += dx;
  center_.y += dy;
}

void Circle::move(const Point &newCenter) { center_ = newCenter; }

void Circle::scale(double coefficient) {
  if (coefficient <= 0.0) {
    throw std::invalid_argument("Coefficient must be positive");
  }
  radius_ *= coefficient;
}

std::string Circle::getName() const { return "CIRCLE"; }