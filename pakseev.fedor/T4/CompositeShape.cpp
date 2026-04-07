#include "CompositeShape.h"

#include <stdexcept>

Point CompositeShape::getCenter() const {
    if (vec_.empty()) {
        return Point(0.0, 0.0);
    }

    double sumX = 0.0, sumY = 0.0;
    for (const auto& i : vec_ ) {
        Point center = i->getCenter();
        sumX += center.x_;
        sumY += center.y_;
    }
    return Point(sumX / vec_.size(), sumY / vec_.size());
}

double CompositeShape::getArea() const {
    if (vec_.empty()) {
        return 0.0;
    }

    double sumArea = 0.0;
    for (const auto& i : vec_) {
        sumArea += i->getArea();
    }
    return sumArea;
}

void CompositeShape::move(double dx, double dy) {
    for (const auto& i : vec_) {
        i->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (factor < 0.0) {
        throw std::invalid_argument("ERROR: Factor should be > 0");
    }

    Point centerComp = getCenter();
    for (const auto& i : vec_) {
        Point shapeCenter = i->getCenter();
        double dx = shapeCenter.x_ - centerComp.x_;
        double dy = shapeCenter.y_ - centerComp.y_;
        double newDx = dx * factor;
        double newDy = dy * factor;
        Point newShapeCenter(
            centerComp.x_ + newDx,
            centerComp.y_ + newDy
        );
        double moveX = newShapeCenter.x_ - shapeCenter.x_;
        double moveY = newShapeCenter.y_ - shapeCenter.y_;
        i->move(moveX, moveY);
        i->scale(factor);
    }
}
