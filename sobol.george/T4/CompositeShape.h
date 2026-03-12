#ifndef COMPSHAPE
#define COMPSHAPE
#include <iostream>
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
		members.~vector();
	}

	void putInComposite(std::unique_ptr<Shape> shape)
	{
		members.push_back(std::move(shape));
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
		Point center;
		for (size_t i = 0; i < members.size(); i++)
		{
			center.x += members[i]->getCenter().x;
			center.y += members[i]->getCenter().y;
		}
		center.x /= static_cast<double>(members.size());
		center.y /= static_cast<double>(members.size());
		return center;
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

	void printInfoComposite()
	{
		for (size_t i = 0; i < members.size(); i++)
		{
			std::cout << '\t' << members[i]->getName() << ", " << "(" << members[i]->getCenter().x << ", "
				<< members[i]->getCenter().y << "), " << members[i]->getArea() << ",\n";
		}
	}
};


#endif
