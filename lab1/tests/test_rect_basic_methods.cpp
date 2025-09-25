#include <cassert>
#include "../src/rect.hpp"


int main() {
    Rect rect1;
    assert(rect1.getLeft() == 0);
    assert(rect1.getRight() == 0);
    assert(rect1.getTop() == 0);
    assert(rect1.getBottom() == 0);

    Rect rect2(1, 2, 3, 4);
    assert(rect2.getLeft() == 1);
    assert(rect2.getRight() == 2);
    assert(rect2.getBottom() == 3);
    assert(rect2.getTop() == 4);

    Rect rect3 = rect2;
    assert(rect3.getLeft() == rect2.getLeft());
    assert(rect3.getRight() == rect2.getRight());
    assert(rect3.getTop() == rect2.getTop());
    assert(rect3.getBottom() == rect2.getBottom());

    rect3.setAll(5, 6, 7, 8);
    assert(rect3.getLeft() == 5);
    assert(rect3.getRight() == 6);
    assert(rect3.getBottom() == 7);
    assert(rect3.getTop() == 8);

    return 0;
}