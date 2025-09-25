#pragma once
#include <iostream>


class Rect {
private:
    int left_;
    //int right_;
    int width_;
    int bottom_;
    //int top_;
    int height_;

public: // TODO☑: подписать параметры
    Rect(int l, int r, int b, int t);
    Rect();
    Rect(const Rect& other);
    ~Rect();
    
    int getLeft();
    int getRight();
    int getTop();
    int getBottom();
    void setAll(int l, int r, int b, int t);
    void inflate(int amount);
    void inflate(int dw, int dh);
    void inflate(int d_left, int d_right, int d_bottom, int d_top);
    void move(int x);
    void move(int x, int y);

    int getWidth();
    int getHeight();
    int getSquare();

    void setWidth(int w);
    void setHeight(int h);
};

Rect boundingRect(Rect r1, Rect r2);
void printRect(Rect& r);