#include "Point.hpp"

Point::Point(void) : x(0), y(0) {
}

Point::Point(const float x, const float y) : x(x), y(y) {
}

Point::Point(const Point& other) : x(other.x), y(other.y) {
}

Point& Point::operator=(const Point& other) {
    // Since x and y are const, we cannot reassign them
    // This is intentional - points should be immutable after creation
    (void)other;
    return *this;
}

Point::~Point(void) {
}

Fixed Point::getX(void) const {
    return this->x;
}

Fixed Point::getY(void) const {
    return this->y;
}
