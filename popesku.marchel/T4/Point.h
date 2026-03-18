#ifndef POINT_H
#define POINT_H

class Point {
public:
    double x_ = 0.0;
    double y_ = 0.0;

    Point() = default;

    Point(double x_val, double y_val) : x_(x_val),
                                        y_(y_val) {
    }
};
#endif
