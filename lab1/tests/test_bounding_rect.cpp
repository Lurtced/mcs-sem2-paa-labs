#include <cassert>
#include "../src/rect.hpp"


int main() {
    Rect r1(1, 4, 1, 4);
    Rect r2(2, 5, 2, 5);
    Rect r3 = boundingRect(r1, r2);
    assert(r3.getLeft() == 1);
    assert(r3.getRight() == 5);
    assert(r3.getBottom() == 1);
    assert(r3.getTop() == 5);

    return 0;
}