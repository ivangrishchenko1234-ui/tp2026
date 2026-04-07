#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

struct Point {
    double x;
    double y;
    Point() : x(0.0), y(0.0) {}
    Point(double x_val, double y_val) : x(x_val), y(y_val) {}

    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx*dx + dy*dy);
    }

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    Point operator*(double scalar) const {
        return Point(x*scalar, y*scalar);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
} ;

#endif // POINT_H
