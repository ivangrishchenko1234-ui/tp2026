#ifndef _POINT_H_
#define _POINT_H_

struct Point{
  double x_=0.0;
  double y_=0.0;

  Point() = default;
  Point(double nx, double ny) : x_(nx), y_(ny) {};
  Point operator-(const Point& other) const{
    return Point(x_-other.x_,y_-other.y_);
  };
  Point operator+(const Point& other) const{
    return Point(x_+other.x_,y_+other.y_);
  }

  Point& operator+=(const Point& other){
    x_ += other.x_;
    y_ += other.y_;
    return *this;
  }
};

#endif // __POINT_H__
