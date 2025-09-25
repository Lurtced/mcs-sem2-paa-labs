#include <cassert>
#include "../src/rect.hpp"


int main() {
    Rect rect(1, 3, 0, 5);
    rect.move(1);
    assert(rect.getLeft() == 2);
    assert(rect.getRight() == 4);
    rect.move(0, 1);
    assert(rect.getBottom() == 1);
    assert(rect.getTop() == 6);
    rect.inflate(1);
    assert(rect.getLeft() == 1);
    assert(rect.getRight() == 5);
    assert(rect.getBottom() == 0);
    assert(rect.getTop() == 7);
    rect.inflate(1, 0);
    assert(rect.getLeft() == 0);
    assert(rect.getRight() == 6);
    rect.inflate(0, 0, 0, 1);
    assert(rect.getTop() == 8);
}