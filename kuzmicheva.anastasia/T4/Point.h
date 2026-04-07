#ifndef POINT_H
#define POINT_H

struct Point {
    double x;
    double y;
    Point() : x(0.0), y(0.0) {}
    Point(double x_, double y_) : x(x_), y(y_) {}
};

#endif
