#ifndef COMPSHAPE
#define COMPSHAPE
#include <iostream>
#include <memory>
#include <cstdlib>
#include <vector>
#include "ellipse.h"
#include "square.h"
#include "rectangle.h"
#include "shape.h"

class CompositeShape : public Shape
{
private:
    std::vector<std::unique_ptr<Shape>> members;
public:
    CompositeShape() {}
    ~CompositeShape()
    {
        members.clear();
    }
    void putInComposite(std::unique_ptr<Shape> shape)
    {
        if (dynamic_cast<CompositeShape*>(shape.get())) {
            throw std::invalid_argument("Cannot add composite shape to another composite");
        }

        members.push_back(std::move(shape));
    }
    const std::vector<std::unique_ptr<Shape>>& membersAccess()
    {
        return this->members;
    }

    double getArea() const override
    {
        double area = 0;
        for (size_t i = 0; i < members.size(); i++)
        {
            area += members[i]->getArea();
        }
        return area;
    }
    Point getCenter() const override
    {
        double minX = members[0]->getMinX();
        double minY = members[0]->getMinY();
        double maxX = members[0]->getMaxX();
        double maxY = members[0]->getMaxY();

        for (size_t i = 1; i < members.size(); i++)
        {
            if (members[i]->getMinX() < minX) minX = members[i]->getMinX();
            if (members[i]->getMinY() < minY) minY = members[i]->getMinY();
            if (members[i]->getMaxX() > maxX) maxX = members[i]->getMaxX();
            if (members[i]->getMaxY() > maxY) maxY = members[i]->getMaxY();
        }

        return Rectangle(minX, minY, maxX, maxY).getCenter();
    }
    double getMinX() const override
    {
        double minX = members[0]->getMinX();

        for (size_t i = 1; i < members.size(); i++)
        {
            if (members[i]->getMinX() < minX) minX = members[i]->getMinX();
        }
        return minX;
    }
    double getMaxX() const override
    {
        double maxX = members[0]->getMaxX();

        for (size_t i = 1; i < members.size(); i++)
        {
            if (members[i]->getMaxX() > maxX) maxX = members[i]->getMaxX();
        }
        return maxX;
    }
    double getMinY() const override
    {
        double minY = members[0]->getMinY();

        for (size_t i = 1; i < members.size(); i++)
        {
            if (members[i]->getMinY() < minY) minY = members[i]->getMinY();
        }
        return minY;
    }
    double getMaxY() const override
    {
        double maxY = members[0]->getMaxY();

        for (size_t i = 1; i < members.size(); i++)
        {
            if (members[i]->getMaxY() > maxY) maxY = members[i]->getMaxY();
        }
        return maxY;
    }
    std::string getName() const override
    {
        return "COMPOSITE";
    }
    void move(const double& factorX, const double& factorY) override
    {
        for (size_t i = 0; i < members.size(); i++)
        {
            members[i]->move(factorX, factorY);
        }
    }
    void scale(const double& factor) override
    {
        Point commonCenter = this->getCenter();
        for (size_t i = 0; i < members.size(); i++)
        {
            Point shapeCenter = members[i]->getCenter();
            double dx = (shapeCenter.x - commonCenter.x) * factor;
            double dy = (shapeCenter.y - commonCenter.y) * factor;
            Point newShapeCenter(commonCenter.x + dx, commonCenter.y + dy);
            double moveX = newShapeCenter.x - shapeCenter.x;
            double moveY = newShapeCenter.y - shapeCenter.y;
            members[i]->move(moveX, moveY);
            members[i]->scale(factor);
        }
    }
};


#endif
