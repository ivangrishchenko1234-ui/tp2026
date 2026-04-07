#ifndef POINT_H
#define POINT_H
#include <iomanip>

struct Point {
    double x = 0;
    double y = 0;

    Point(double x, double y) :
        x(x),
        y(y)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
        os << "(" << obj.x << ", " << obj.y << ")";
        return os;
    }
};

#endif
