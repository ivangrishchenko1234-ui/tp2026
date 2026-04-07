#include <stdexcept>

#include "ring.h"

static const double pi = 3.14159;

Ring::Ring(const Point& center, const double r1,const double r2) : center_(center), radiusBig_(r1), radiusSmall_(r2)
{
  if (r1 <= 0 || r2 <= 0) {
    throw std::invalid_argument("Radii must be positive");
  }
  else if(r1<r2){
    throw std::invalid_argument("r1 must be bigger r2");
  }
}

double Ring::getArea() const
{
  return (pi*(radiusBig_*radiusBig_-radiusSmall_*radiusSmall_));
}

Point Ring::getCenter() const
{
  return center_;
}

void Ring::move(double dx,double dy)
{
  center_+=Point(dx,dy);
}

void Ring::scale(double factor)
{
  if (factor<=0) {
    throw std::invalid_argument("factor must be > 0");
  }
  radiusBig_*=factor;
  radiusSmall_*=factor;
}

std::string Ring::getName() const
{
  return "Ring";
}
