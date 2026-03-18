#ifndef ISOSCELESTRAPEZOID_H
#define ISOSCELESTRAPEZOID_H

#include "Shape.h"

class IsoscelesTrapezoid : public Shape {
public:
    IsoscelesTrapezoid(const Point &bottomL, double bottomB, double topB, double h);

    double getArea() const override;

    Point getCenter() const override;

    void move(double dx, double dy) override;

    void scale(double factor) override;

    std::string getName() const override;

    void print() const override;

private:
    Point bottomLeft_;
    double bottomBase_;
    double topBase_;
    double height_;
};


#endif
