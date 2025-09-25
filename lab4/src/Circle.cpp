#include "Circle.hpp"
#include "Point.hpp"
#include <iostream>
#include <cmath>


Circle::Circle() : center_(Point()), radius_(0.0) {}

Circle::Circle(double x, double y, double radius)
    : center_(Point(x, y)), radius_(radius) {}

Circle::Circle(Point& point, double radius)
    : center_(point), radius_(radius) {}

Point Circle::getCenter() const {
    return center_;
}

double Circle::getRadius() const {
    return radius_;
}

void Circle::setCenter(double x, double y) {
    center_.setX(x);
    center_.setY(y);
}

void Circle::setCenter(Point& point) {
    center_ = point;
}

void Circle::setRadius(double radius) {
    radius_ = radius;
}

void Circle::print() const {
    std::cout << "Circle: Center = ";
    center_.print();
    std::cout << "Radius = " << radius_ << std::endl;
}

bool Circle::operator ==(const Circle& other) const {
    if ((center_ == other.center_) && (radius_ == other.radius_))
        return true;
    else
        return false;
}

Circle& Circle::operator =(const Circle& other) {
    center_ = other.center_;
    radius_ = other.radius_;
    return *this;
}

double Circle::getArea() const {
    return M_PI * radius_ * radius_;
}

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    os << "Circle: Center = (" 
       << circle.center_.getX() << ", " 
       << circle.center_.getY() 
       << "), Radius = " << circle.radius_;
    return os;
}