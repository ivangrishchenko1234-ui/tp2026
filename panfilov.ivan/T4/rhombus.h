#ifndef RHOMBUS_H
#define RHOMBUS_H
#include "shape.h"

class Rhombus : public Shape {
private:
    Point center;
    double verticalDiagonal;
    double horizontalDiagonal;
public:
    Rhombus(const Point& c, double vd, double hd);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif
