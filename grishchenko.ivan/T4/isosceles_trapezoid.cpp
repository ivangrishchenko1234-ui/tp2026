#include"isosceles_trapezoid.h"
#include<stdexcept>
IsoscelesTrapezoid::IsoscelesTrapezoid(const Point&leftBottom,double bottomBase,
double topBase,double height)
:leftBottom_(leftBottom),bottomBase_(bottomBase),
topBase_(topBase),height_(height){
if(bottomBase<=0||topBase<=0||height<=0){
throw std::invalid_argument("Basesandheightmustbepositive");
}
if(topBase>bottomBase){
throw std::invalid_argument("Topbasemustbelessthanorequaltobottombase");
}
}
double IsoscelesTrapezoid::getArea()const{
return(bottomBase_+topBase_)*height_/2.0;
}
Point IsoscelesTrapezoid::getCenter()const{
Point center;
double offset=(bottomBase_-topBase_)/2.0;
center.x=leftBottom_.x+bottomBase_/2.0;
center.y=leftBottom_.y+height_/2.0;
return center;
}
void IsoscelesTrapezoid::move(double dx,double dy){
leftBottom_.x+=dx;
leftBottom_.y+=dy;
}
void IsoscelesTrapezoid::scale(double factor){
Point center=getCenter();
leftBottom_.x=center.x+(leftBottom_.x-center.x)*factor;
leftBottom_.y=center.y+(leftBottom_.y-center.y)*factor;
bottomBase_*=factor;
topBase_*=factor;
height_*=factor;
}
std::string IsoscelesTrapezoid::getName()const{
return"ISOSCELES_TRAPEZOID";
}
