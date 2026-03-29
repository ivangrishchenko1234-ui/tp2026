#ifndef POINT_H
#define POINT_H

struct Point
{
    double x_;
    double y_;

    Point(double x = 0.0, double y = 0.0);
};

inline Point::Point(double x, double y) :
    x_(x),
    y_(y)
{
}

#endif
