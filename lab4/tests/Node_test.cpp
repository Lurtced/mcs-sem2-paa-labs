#include "../src/Node.hpp"
#include <iostream>

int main() {
    std::cout << "Running Node tests..." << std::endl;

    Circle c1(0, 0, 5);
    Node node1(c1);
    node1.print();

    Circle c2(10, 10, 15);
    Node node2(c2);
    node2.print();

    node1.setNext(&node2);
    node2.setPrev(&node1);

    std::cout << "After linking nodes:" << std::endl;
    node1.print();
    node2.print();

    std::cout << "Node test completed." << std::endl;
    return 0;
}