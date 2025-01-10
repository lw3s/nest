#include <cmath>


int gcf(int a, int b) {
    a = std::abs(a); b = std::abs(b);
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int lcm(int a, int b) {
    return a * b / gcf(a, b);
}