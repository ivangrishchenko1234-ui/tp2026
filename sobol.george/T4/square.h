#ifndef SQUARE
#define SQUARE
#include <iostream>
#include <cstdlib>
#include <memory>
#include "shape.h"

class Square : public Shape
{
private:
    Point botLet;
    double length;
public:
    Square(const Point& tl, const double& l) : botLet(tl), length(l)
    {}
    ~Square() override
    {}
    double getArea() const override
    {
        return length * length;
    }
    Point getCenter() const override
    {
        Point center;
        center.x = botLet.x + length / 2;
        center.y = botLet.y + length / 2;
        return center;
    }
    std::string getName() const override { return "SQUARE"; }
    void move(const double& factorX, const double& factorY) override
    {
        botLet.x += factorX;
        botLet.y += factorY;
    }
    void scale(const double& factor) override
    {
        Point center = this->getCenter();
        botLet.x = center.x + (botLet.x - center.x) * factor;
        botLet.y = center.y + (botLet.y - center.y) * factor;
        length *= factor;
    }
    double getMinX() const override
    {
        return botLet.x;
    }
    double getMaxX() const override
    {
        return botLet.x + length;
    }
    double getMinY() const override
    {
        return botLet.y;
    }
    double getMaxY() const override
    {
        return botLet.y + length;
    }
};

#endif
