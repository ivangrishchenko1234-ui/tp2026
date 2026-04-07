#include "Ring.h"
#include <cmath>
#include <stdexcept>
#include <string>
#include <memory>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Ring::Ring(const Point& center, double outRad, double inRad)
: center_(center), outR_(outRad), inR_(inRad) {
if (outR_ <= 0 || inR_ < 0) {
throw std::invalid_argument("Invalid radii values.");
}

if (outR_ <= inR_) {
throw std::invalid_argument("Outer radius must be greater than inner radius.");
}
}

double Ring::getArea() const {
return M_PI * (outR_ * outR_ - inR_ * inR_);
}

Point Ring::getCenter() const {
return center_;
}

void Ring::move(double dx, double dy) {
center_.x += dx;
center_.y += dy;
}

void Ring::scale(double factor) {
if (factor <= 0) {
throw std::invalid_argument("Scale factor must be positive.");
}

double newOutR = outR_ * factor;
double newInR = inR_ * factor;

if (newOutR <= newInR) {
throw std::invalid_argument("Scaling violates radii ratio.");
}

outR_ = newOutR;
inR_ = newInR;
}

std::string Ring::getName() const {
return "RING";
}

std::unique_ptr<Shape> Ring::clone() const {
return std::make_unique<Ring>(*this);
}
