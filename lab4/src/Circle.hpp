#pragma once
#include "Point.hpp"
#include <ostream>

class Circle {
private:
    Point center_;
    double radius_;

public:
    Circle();
    Circle(double x, double y, double radius);
    Circle(Point& point, double radius);
    Point getCenter() const;
    double getRadius() const;
    void setCenter(double x, double y);
    void setCenter(Point& point);
    void setRadius(double radius);
    void print() const;
    double getArea() const;

    bool operator ==(const Circle& other) const;
    Circle& operator =(const Circle& other);
    friend std::ostream& operator<<(std::ostream& os, const Circle& circle);
};