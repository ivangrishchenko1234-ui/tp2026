#include "utils.h"

std::string formatShapeInfo(const std::string& name, const Point& center, double area) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "[" << name << ", (" << center.x << ", " << center.y << "), " << area << "]";
    return oss.str();
}
