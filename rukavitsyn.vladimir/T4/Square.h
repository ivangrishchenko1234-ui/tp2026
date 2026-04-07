#include "Shape.h"
#include <string>
#include <utility>

class Square : public Shape {
private:
    Point bottomLeft_;
    double length_;
public:
    Square(const Point& bl, const double len) :
        bottomLeft_(bl),
        length_(len)
    {
    }
    double getArea() const override { return length_ * length_; }
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::pair<Point, Point> circumscribedRectangle() const override;

    void print(std::ostream& stream) const;
};
