#ifndef POINT_H
#define POINT_H

struct Point {
    double x;
    double y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    Point operator*(double factor) const {
        return Point(x * factor, y * factor);
    }
};

#endif
