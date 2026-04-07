#include "rombus.h"
#include <stdexcept>

Rombus::Rombus(const Point &center, double verticalDiagonal, double horizontalDiagonal)
    : center_(center), verticalDiagonal_(verticalDiagonal), horizontalDiagonal_(horizontalDiagonal) {
    if (verticalDiagonal <= 0.0 || horizontalDiagonal <= 0.0) {
        throw std::invalid_argument("Diagonals must be positive");
    }
}

double Rombus::getArea() const {
    return (verticalDiagonal_ * horizontalDiagonal_) / 2.0;
}

Point Rombus::getCenter() const {
    return center_;
}

void Rombus::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
}

void Rombus::move(const Point &newCenter) {
    center_ = newCenter;
}

void Rombus::scale(double factor) {
    if (factor <= 0.0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    verticalDiagonal_ *= factor;
    horizontalDiagonal_ *= factor;
}

std::string Rombus::getName() const {
    return "ROMBUS";
}
