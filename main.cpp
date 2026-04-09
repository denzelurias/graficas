#include <iostream>

int main() {
    int cinco = 5;
    int *p = &cinco;
    int *q = &cinco;

    if (p == q) {
        std::cout << "SON IGUALES\n";
    }

    std::cout << "Valor de la variable cinco: " << *p << '\n';
    std::cout << "Dirección de la variable cinco: " << p << '\n';
    std::cout << "Dirección de la variable cinco: " << &cinco << '\n';

}