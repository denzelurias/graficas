//
// Created by denze on 4/7/2026.
//

#ifndef GRAFICA_GRAFICA_H
#define GRAFICA_GRAFICA_H

#include <string>

struct Nodo;
class Grafica {
public:

    Grafica();

    void agregarNodo(std::string nombre);
    void agregarArista(std::string nodo1, std::string nodo2);

    void eliminarNodo(std::string nombre);
    void eliminarArista(std::string nodo1, std::string nodo2);
    

    bool estaVacia() const;

private:
    unsigned int num_nodos_;
    unsigned int num_aristas_;
    Nodo *primer_nodo_;
    Nodo *ultimo_nodo_;

};

struct Arista;
struct Nodo {
    std::string nombre_nodo_;
    unsigned int grado_nodo_;

    Arista *primera_arista_;
    Arista *ultima_arista_;

    Nodo *siguiente_nodo_;

    Nodo(std::string nombre, Nodo *siguiente = nullptr);

};

struct Arista {
    Nodo *adyacente_;

    Arista *siguiente_arista_;

    Arista(Nodo *adyacente, Arista *siguiente = nullptr);
};


#endif //GRAFICA_GRAFICA_H