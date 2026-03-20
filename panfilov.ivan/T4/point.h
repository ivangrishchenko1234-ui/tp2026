#ifndef POINT_H
#define POINT_H

struct Point {
    double x_;
    double y_;
    Point() {
        x_ = 0;
        y_ = 0;
    }
    Point(double x, double y) {
        x_ = x;
        y_ = y;
    }
};

#endif

