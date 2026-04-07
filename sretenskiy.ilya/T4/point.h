#ifndef POINT_H
#define POINT_H

struct Point {
    double x = 0.0;
    double y = 0.0;

    Point() = default;
    Point(double x_, double y_) : x(x_), y(y_) {}
};

#endif
