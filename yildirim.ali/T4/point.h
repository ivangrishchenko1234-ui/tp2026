#ifndef POINT_H
#define POINT_H

struct Point {
    double x = 0.0;
    double y = 0.0;

    Point() = default;
    Point(double x_val, double y_val) : x(x_val), y(y_val) {}
};

#endif
//
