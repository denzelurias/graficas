#include <iostream>

#include "grafica.h"

int main() {
    Grafica grafica;

    grafica.agregarNodo("A");
    grafica.agregarNodo("B");
    grafica.agregarNodo("C");
    grafica.agregarNodo("D");
    grafica.agregarNodo("E");
    grafica.agregarNodo("F");
    grafica.agregarNodo("G");

    grafica.agregarArista("A", "B", 7.0);
    grafica.agregarArista("A", "D", 5.0);
    grafica.agregarArista("B", "C", 8.0);
    grafica.agregarArista("B", "D", 9.0);
    grafica.agregarArista("B", "E", 7.0);
    grafica.agregarArista("C", "E", 5.0);
    grafica.agregarArista("D", "E", 15.0);
    grafica.agregarArista("D", "F", 6.0);
    grafica.agregarArista("E", "F", 8.0);
    grafica.agregarArista("E", "G", 9.0);
    grafica.agregarArista("F", "G", 11.0);

    std::cout << "Grafica original:\n";
    grafica.imprimir();
    std::cout << '\n';

    Grafica arbol = grafica.arbolMinimaExpansionPrim();

    std::cout << "Arbol de minima expansion (Prim):\n";
    if (arbol.estaVacia()) {
        std::cout << "La grafica no es conexa.\n";
        return 0;
    }

    arbol.imprimir();
    std::cout << '\n';

    std::cout << "Orden: " << arbol.orden() << '\n';
    std::cout << "Tamano: " << arbol.tamano() << '\n';

    return 0;
}
