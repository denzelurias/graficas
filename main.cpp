#include <iostream>

int main() {
    int cinco = 5;
    int *p = &cinco;
    int *q = &cinco;

    if (p == q) {
        std::cout << "SON IGUALES\n";
    }
}