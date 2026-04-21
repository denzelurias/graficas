#include <iostream>

#include "grafica.h"

int main() {
    Grafica fer;

    fer.agregarNodo("a");
    fer.agregarNodo("b");
    fer.agregarNodo("c");
    fer.agregarNodo("d");

    fer.agregarArista("a", "b");
    fer.agregarArista("b", "c");
    fer.agregarArista("c", "d");
    fer.agregarArista("d", "a");

    fer.imprimir();
    std::cout << '\n';

    fer.eliminarNodo("d");
    fer.agregarNodo("d");

    fer.imprimir();
    std::cout << '\n';

    fer.agregarNodo("a");

}
