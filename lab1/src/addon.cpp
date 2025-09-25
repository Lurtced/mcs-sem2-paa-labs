#include "addon.hpp"

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void swap(int& a, int& b) {
    int buff = a;
    a = b;
    b = a;
}