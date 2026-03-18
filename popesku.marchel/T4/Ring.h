#ifndef RING_H
#define RING_H

#include "Shape.h"

class Ring : public Shape {
public:
    Ring(const Point &c, double outerR, double innerR);

    double getArea() const override;

    Point getCenter() const override;

    void move(double dx, double dy) override;

    void scale(double factor) override;

    std::string getName() const override;

    void print() const override;

private:
    Point center_;
    double outerRadius_;
    double innerRadius_;
};


#endif //WORKOUT_RING_H
