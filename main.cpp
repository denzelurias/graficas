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

    fer.eliminarArista("a", "d");
    fer.agregarArista("a", "d");

    fer.imprimir();


}
