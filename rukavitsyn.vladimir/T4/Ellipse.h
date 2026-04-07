#include "Shape.h"

class Ellipse : public Shape {
private:
    double radX_;
    double radY_;
    Point center_;
public:
    Ellipse(double rX, double rY, Point c) :
        radX_(rX),
        radY_(rY),
        center_(c)
    {
    }
    double getArea() const override;
    Point getCenter() const override { return center_; }
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> circumscribedRectangle() const override;

    void print(std::ostream& stream) const override;
};
