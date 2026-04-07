#include "Ring.h"

void Ring::move(double dx, double dy) {
    center_.x_ += dx;
    center_.y_ += dy;
}

void Ring::scale(double factor) {
    radiusIn_ *= factor;
    radiusOut_ *= factor;
}
