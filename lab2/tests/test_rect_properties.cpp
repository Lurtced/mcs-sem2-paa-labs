#include <cassert>
#include "../src/rect.hpp"


int main() {
    Rect rect(1, 3, 3, 6);
    assert(rect.getWidth() == 2);
    assert(rect.getHeight() == 3);
    assert(rect.getSquare() == 6);
    rect.setWidth(5);
    assert(rect.getWidth() == 5);
    rect.setHeight(5);
    assert(rect.getHeight() == 5);

    return 0;
}