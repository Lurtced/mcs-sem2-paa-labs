#pragma once

class Point {
private:
    double x_;
    double y_;

public:
    Point();
    Point(double x, double y);
    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);
    void print() const;

    bool operator ==(const Point& other) const;
    Point& operator =(const Point& other);
};