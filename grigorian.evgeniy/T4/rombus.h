#ifndef ROMBUS_H
#define ROMBUS_H

#include "shape.h"

class Rombus : public Shape {
public:
    Rombus(const Point &center, double verticalDiagonal, double horizontalDiagonal);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void move(const Point &newCenter) override;
    void scale(double factor) override;
    std::string getName() const override;

private:
    Point center_;
    double verticalDiagonal_;
    double horizontalDiagonal_;
};

#endif
