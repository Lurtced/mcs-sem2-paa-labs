#include "Point.hpp"
#include <iostream>

Point::Point() : x_(0.0), y_(0.0) {}

Point::Point(double x, double y) : x_(x), y_(y) {}

double Point::getX() const {
    return x_;
}

double Point::getY() const {
    return y_;
}

void Point::setX(double x) {
    x_ = x;
}

void Point::setY(double y) {
    y_ = y;
}

void Point::print() const {
    std::cout << "Point(" << x_ << ", " << y_ << ")" << std::endl;
}

bool Point::operator ==(const Point& other) const {
    if (x_ == other.x_ && y_ == other.y_)
        return true;
    else
        return false;
}

Point& Point::operator =(const Point& other) {
    x_ = other.x_;
    y_ = other.y_;
    return *this;
}