#include "../src/List.hpp"
#include <iostream>

int main() {
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
    list.addBack(Circle(1, 2, 3));
    list.addBack(Circle(0, 0, 0));
    std::cout << "Removed " << list.removeAll(toRemove) << " elements. Current size is " << list.size() << std::endl;

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

    return 0;
}