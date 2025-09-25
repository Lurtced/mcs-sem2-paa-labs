#include "rect.hpp"
#include "addon.hpp"
#include <iostream>

// Rect::Rect(const Rect& other) : left_(other.left_), right_(other.right_), bottom_(other.bottom_), top_(other.top_) {
//     std::cout << "Copy constructor called at " << this << std::endl;
// }
// Rect::Rect(int l, int r, int b, int t) : left_(min(l, r)), right_(max(r, l)), bottom_(min(b, t)), top_(max(t, b)) {
//     std::cout << "Parameterized constructor called at " << this << std::endl;
// }
// Rect::Rect() : left_(0), right_(0), bottom_(0), top_(0) {
//     std::cout << "Default constructor called at " << this << std::endl;
// }

Rect::Rect() : left_(0), width_(0), bottom_(0), height_(0) {
    std::cout << "Default constructor called at " << this << std::endl;
}

Rect::Rect(const Rect& other) : left_(other.left_), width_(other.width_), bottom_(other.bottom_), height_(other.height_) {
    std::cout << "Copy constructor called at " << this << std::endl;
}

Rect::Rect(int l, int r, int b, int t) : left_(l), width_(r - l), bottom_(b), height_(t - b) {
    std::cout << "Parameterized constructor called at " << this << std::endl;
}

Rect::~Rect() {
    std::cout << "Destructor is called at " << this << std::endl;
}

int Rect::getLeft() { return left_; }
// int Rect::getRight() { return right_; }
int Rect::getRight() {return left_ + width_; }
int Rect::getBottom() { return bottom_; }
//int Rect::getTop() { return top_; }
int Rect::getTop() {return bottom_ + height_; }

// void Rect::setAll(int l, int r, int b, int t) {
//     left_ = min(l, r);
//     right_ = max(r, l);
//     bottom_ = min(b, t);
//     top_ = max(t, b);
// }

void Rect::setAll(int l, int r, int b, int t) {
    left_ = l;
    width_ = r - l;
    bottom_ = b;
    height_ = t - b;
}

// void Rect::inflate(int amount) {
//     left_ -= amount;
//     right_ += amount;
//     bottom_ -= amount;
//     top_ += amount;
// }

void Rect::inflate(int amount) {
    left_ -= amount;
    bottom_ -= amount;
    width_ += amount * 2; // "shift"
    height_ += amount * 2; // "shift"
}

// void Rect::inflate(int dw, int dh) {
//     left_ -= dw;
//     right_ += dw;
//     bottom_ -= dh;
//     top_ += dh;
// }

void Rect::inflate(int dw, int dh) {
    left_ -= dw;
    width_ += dw * 2; // "shift"
    bottom_ -= dh;
    height_ += dh * 2; // "shift"
}

// void Rect::inflate(int d_left, int d_right, int d_bottom, int d_top) {
//     left_ -= d_left;
//     right_ += d_right;
//     bottom_ -= d_bottom;
//     top_ += d_top;
// }

void Rect::inflate(int d_left, int d_right, int d_bottom, int d_top) {
    left_ -= d_left;
    width_ += d_right + d_left; // "+ d_left" because it will "shift" when moving left_
    bottom_ -= d_bottom;
    height_ += d_top + d_bottom; // "+ d_bottom" because it will "shift" when moving bottom_
}

// void Rect::move(int x) {
//     left_ += x;
//     right_ += x;
// }

void Rect::move(int x) { left_ += x; }

// void Rect::move(int x, int y) {
//     left_ += x;
//     right_ += x;
//     bottom_ += y;
//     top_ += y;
// }

void Rect::move(int x, int y) {
    left_ += x;
    bottom_ += y;
}

// int Rect::getWidth() {
//     return right_ - left_;
// }

int Rect::getWidth() { return width_; }

// int Rect::getHeight() {
//     return top_ - bottom_;
// }

int Rect::getHeight() { return height_; }

// int Rect::getSquare() {
//     return (right_ - left_) * (top_ - bottom_);
// }

int Rect::getSquare() { return width_ * height_; }

// void Rect::setWidth(int w) {
//     right_ = left_ + w;
//     if (right_ < left_) {
//         swap(right_, left_);
//     }
// }

void Rect::setWidth(int w) { width_ = w; }

// void Rect::setHeight(int h) {
//     top_ = bottom_ + h;
//     if (top_ < bottom_) {
//         swap(top_, bottom_);
//     }
// }

void Rect::setHeight(int h) { height_ = h; }

Rect boundingRect(Rect r1, Rect r2) {
    Rect r3(min(r1.getLeft(), r2.getLeft()),
            max(r1.getRight(), r2.getRight()), 
            min(r1.getBottom(), r2.getBottom()), 
            max(r1.getTop(), r2.getTop()));
    return r3;
}

void printRect(Rect &r) {
    std::cout << r.getLeft() << ", " 
              << r.getRight() << ", " 
              << r.getBottom() << ", " 
              << r.getTop() << std::endl;
}