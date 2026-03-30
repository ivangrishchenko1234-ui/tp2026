#include "ring.h"
#include <cmath>
#include <stdexcept>

Ring::Ring(const Point& center, double rad1, double rad2)
{
    if (rad1 <= 0.0 || rad2 <= 0.0)
    {
        throw std::invalid_argument("Invalid ring radius");
    }

    if (rad1 == rad2)
    {
        throw std::invalid_argument("Ring radii must be different");
    }

    center_ = center;

    if(rad1 > rad2)
    {
        innerRadius_ = rad2;
        outerRadius_ = rad1;
    }
    else
    {
        innerRadius_ = rad1;
        outerRadius_ = rad2;
    }
}

double Ring::getArea() const
{
    return M_PI * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
}

Point Ring::getCenter() const
{
    return center_;
}

void Ring::move(const Point& newCenter)
{
    center_ = newCenter;
}

void Ring::scale(double ratio)
{
    if (ratio <= 0.0)
    {
        throw std::invalid_argument("Ratio must be positive");
    }

    innerRadius_ *= ratio;
    outerRadius_ *= ratio;
}

std::string Ring::getName() const
{
    return "Ring";
}
