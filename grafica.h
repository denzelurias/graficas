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
    Grafica(const Grafica &graf);
    ~Grafica();

    Grafica& operator=(const Grafica &graf);

    void agregarNodo(const std::string &nombre);
    void agregarArista(const std::string &nodo1, const std::string &nodo2);

    void eliminarNodo(const std::string &nombre);
    void eliminarArista(const std::string &nodo1, const std::string &nodo2);

    bool buscarNodo(const std::string &nodo) const;
    bool buscarArista(const std::string &nodo1, const std::string &nodo2) const;

    int gradoNodo(const std::string &nodo) const;

    void vaciarNodo(const std::string &nodo);
    void vaciarGrafica();

    unsigned int orden() const;
    unsigned int tamano() const;

    bool estaVacia() const;

    void imprimir() const;

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
