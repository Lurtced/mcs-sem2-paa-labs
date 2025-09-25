#include "Node.hpp"
#include "Circle.hpp"
#include "List.hpp"
#include <iostream>

int main() {
    {
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
    }

    {
        std::cout << "Running Node tests..." << std::endl;

        Circle c1(0, 0, 5);
        Node node1(c1);
        node1.print();

        Circle c2(10, 10, 15);
        Node node2(c2);
        node2.print();

        // Связываем узлы
        node1.setNext(&node2);
        node2.setPrev(&node1);

        std::cout << "After linking nodes:" << std::endl;
        node1.print();
        node2.print();

        std::cout << "Node test completed." << std::endl;
    }

    {
        List list;

        list.addBack(Circle(1, 2, 3));
        list.addBack(Circle(4, 5, 6));
        list.addFront(Circle(0, 0, 0));

        std::cout << "Size of list: " << list.size() << std::endl;

        Circle toRemove(1, 2, 3);
        if (list.remove(toRemove)) {
            std::cout << "Element removed successfully." << std::endl;
        } else {
            std::cout << "Element not found." << std::endl;
        }

        list.clear();
        std::cout << "Size after clearing: " << list.size() << std::endl;

        std::cout << "Adding two same elements and one different and trying to delete the same." << std::endl;
        list.addBack(Circle(1, 2, 3));
        list.addBack(Circle(0, 0, 0));
        list.addBack(Circle(1, 2, 3));
        list.addBack(Circle(0, 0, 0));
        std::cout << "List before: \n" << list << std::endl;
        std::cout << "Removed " << list.removeAll(toRemove) << " elements. Current size is " << list.size() << std::endl;
        std::cout << "List after: \n" << list << std::endl;

        std::cout << "Sort test. Adding several elements." << std::endl;
        list.addFront(Circle(1, 2, 3));
        list.addFront(Circle(1, 2, 4));
        list.addFront(Circle(1, 2, 5));
        list.addFront(Circle(1, 2, 1));
        std::cout << list;
        list.sortByArea();
        std::cout << list;

        std::cout << "Saving to file 'list_save.txt'" << std::endl;
        list.saveToFile("list_save.txt");

        std::cout << "Clearing list." << std::endl;
        list.clear();
        std::cout << list;
        std::cout << "Loading from file..." << std::endl;
        list.loadFromFile("list_save.txt");
        std::cout << list;

        std::cout << "Testing copying..." << std::endl;
        List copy1 = list;
        List copy2(list);
        std::cout << copy1;
        std::cout << copy2;

        std::cout << "Get element with index 2: " << list.get(2) << std::endl;
        std::cout << "Example of going through the whole list: " << std::endl;
        for (auto i = list.begin(); i != list.end(); ++i) {
            std::cout << "Element: " << i << std::endl;
        }
        std::cout << "How to get their radiuses: " << std::endl;
        for (auto i = list.begin(); i != list.end(); ++i) {
            std::cout << "Element: " << i->getRadius() << std::endl;
        }
        std::cout << "How to print their areas: " << std::endl;
        for (auto i = list.begin(); i != list.end(); ++i) {
            std::cout << "Element: " << i->getArea() << std::endl;
        }
    }

    return 0;
}