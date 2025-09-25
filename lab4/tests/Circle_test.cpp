#include "../src/Circle.hpp"
#include <iostream>

int main() {
    std::cout << "Running Circle tests..." << std::endl;

    Circle c1(0, 0, 5);
    c1.print();

    c1.setRadius(7);
    c1.setCenter(2, 3);
    c1.print();

    Point p(4, 5);
    c1.setCenter(p);
    c1.print();

    std::cout << "Circle test completed." << std::endl;
    return 0;
}