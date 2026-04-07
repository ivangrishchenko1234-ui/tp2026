#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include "shape.h"
#include "rectangle.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape{
public:
    CompositeShape() = default;

    void addShape(std::unique_ptr<Shape> shape);

   double getArea() const override;
   Point getCenter() const override;
   void move(double dx, double dy) override;
   void scale(double factor) override;
   std::string getName() const override;
private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};

#endif // __COMPLEX_H__
