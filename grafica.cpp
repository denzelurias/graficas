//
// Created by denze on 4/7/2026.
//

#include <iostream>
#include "grafica.h"

//----------------------------------------------------------------------
// Grafica
//----------------------------------------------------------------------

Grafica::Grafica()
        : num_nodos_{0},
        num_aristas_{0},
        primer_nodo_{nullptr},
        ultimo_nodo_{nullptr} {}

/*
Grafica::Grafica(const Grafica &graf) {
    this =
}
*/

Grafica::~Grafica() {
    vaciarGrafica();
}

Grafica Grafica::operator=(const Grafica &graf) {

}

void Grafica::agregarNodo(std::string nombre) {
    try {
        Nodo *nuevo_nodo = new Nodo(nombre);

        if(ultimo_nodo_ == nullptr) {
            primer_nodo_ = nuevo_nodo;
            ultimo_nodo_ = nuevo_nodo;
        }
        else {
            ultimo_nodo_->siguiente_nodo_ = nuevo_nodo;
            ultimo_nodo_ = nuevo_nodo;
        }
        ++num_nodos_;
    }
    catch (const std::bad_alloc &mensaje) {
        std::cerr << "Error de memoria: " << mensaje.what() << '\n';
    }
}

void Grafica::agregarArista(std::string nodo1, std::string nodo2) {
    try {
        Nodo *puntero = primer_nodo_;

        Nodo *aux_uno = nullptr;
        Nodo *aux_dos = nullptr;

        while (puntero != nullptr) {
            if (puntero->nombre_nodo_ == nodo1) {
                aux_uno = puntero;
            }
            if (puntero->nombre_nodo_ == nodo2) {
                aux_dos = puntero;
            }

            if (aux_uno != nullptr && aux_dos != nullptr) {
                break;
            }

            puntero = puntero->siguiente_nodo_;
        }

        if (aux_uno == nullptr || aux_dos == nullptr) {
            std::cerr << "Error: No se encontró alguno de los nodos.\n";
            return;
        }

        Arista *nueva_arista = new Arista(aux_dos);

        if (aux_uno->ultima_arista_ == nullptr) {
            aux_uno->primera_arista_ = nueva_arista;
            aux_uno->ultima_arista_ = nueva_arista;
        }
        else {
            aux_uno->ultima_arista_->siguiente_arista_ = nueva_arista;
            aux_uno->ultima_arista_ = nueva_arista;
        }

        Arista *nueva_arista_dos = new Arista(aux_uno);

        if (aux_dos->ultima_arista_ == nullptr) {
            aux_dos->primera_arista_ = nueva_arista_dos;
            aux_dos->ultima_arista_ = nueva_arista_dos;
        }
        else {
            aux_dos->ultima_arista_->siguiente_arista_ = nueva_arista_dos;
            aux_dos->ultima_arista_ = nueva_arista_dos;
        }

        ++aux_uno->grado_nodo_;
        ++aux_dos->grado_nodo_;

    }
    catch (const std::bad_alloc &mensaje) {
        std::cerr << "Error de memoria: " << mensaje.what() << '\n';
    }
}

// ARREGLAR ERROR, NO ACTUALIZA BIEN ultimo_nodo_
void Grafica::eliminarNodo(std::string nombre) {
    if (estaVacia()) {
        std::cerr << "Error: El la gráfica está vacía.\n";
        return;
    }

    Nodo *puntero = primer_nodo_;

    // En el caso que eliminemos el primer nodo
    if (puntero->nombre_nodo_ == nombre) {
        while (primer_nodo_->primera_arista_ != nullptr) {
            eliminarArista(primer_nodo_->nombre_nodo_, primer_nodo_->primera_arista_->adyacente_->nombre_nodo_);
        }

        primer_nodo_ = primer_nodo_->siguiente_nodo_;
        delete puntero;

        --num_nodos_;
    }
    // En el caso que NO eliminemos el primero nodo
    else {
        Nodo *porBorrar = puntero->siguiente_nodo_;

        while (porBorrar != nullptr) {
            if (porBorrar->nombre_nodo_ == nombre) {
                break;
            }

            puntero = puntero->siguiente_nodo_;
            porBorrar = porBorrar->siguiente_nodo_;
        }

        if (porBorrar == nullptr) {
            std::cerr << "Error: No se encontró alguno de los nodos.\n";
            return;
        }

        while (porBorrar->primera_arista_ != nullptr) {
            eliminarArista(porBorrar->nombre_nodo_, porBorrar->primera_arista_->adyacente_->nombre_nodo_);
        }

        puntero->siguiente_nodo_ = porBorrar->siguiente_nodo_;
        delete porBorrar;

        --num_nodos_;
    }
}

// ARREGLAR ERROR, NO ACTUALIZA BIEN ultima_arista_
void Grafica::eliminarArista(std::string nodo1, std::string nodo2) {
    Nodo *puntero = primer_nodo_;

    Nodo *aux_uno = nullptr;
    Nodo *aux_dos = nullptr;

    while (puntero != nullptr) {
        if (puntero->nombre_nodo_ == nodo1) {
            aux_uno = puntero;
        }
        if (puntero->nombre_nodo_ == nodo2) {
            aux_dos = puntero;
        }

        if (aux_uno != nullptr && aux_dos != nullptr) {
            break;
        }

        puntero = puntero->siguiente_nodo_;
    }

    if (aux_uno == nullptr || aux_dos == nullptr) {
        std::cerr << "Error: No se encontró alguno de los nodos.\n";
        return;
    }

    if (aux_uno->primera_arista_ == nullptr || aux_dos->primera_arista_ == nullptr) {
        std::cerr << "Error: No existe la arista.\n";
        return;
    }

    Arista *porBorrar = nullptr;

    // En el caso que eliminemos la primera arista
    if (aux_uno->primera_arista_->adyacente_->nombre_nodo_ == aux_dos->nombre_nodo_) {
        porBorrar = aux_uno->primera_arista_;
        aux_uno->primera_arista_ = porBorrar->siguiente_arista_;
        delete porBorrar;
    }
    else {
        // En el caso que NO sea la primera arista
        Arista *anterior = aux_uno->primera_arista_;
        porBorrar = anterior->siguiente_arista_;

        while (porBorrar != nullptr) {
            if (porBorrar->adyacente_->nombre_nodo_ == aux_dos->nombre_nodo_) {
                anterior->siguiente_arista_ = porBorrar->siguiente_arista_;
                delete porBorrar;
                break;
            }

            anterior = anterior->siguiente_arista_;
            porBorrar = anterior->siguiente_arista_;
        }
    }

    //------------------------------------------------------

    porBorrar = nullptr;

    // En el caso que eliminemos la primera arista
    if (aux_dos->primera_arista_->adyacente_->nombre_nodo_ == aux_uno->nombre_nodo_) {
        porBorrar = aux_dos->primera_arista_;
        aux_dos->primera_arista_ = porBorrar->siguiente_arista_;
        delete porBorrar;
    }
    else {
        // En el caso que NO sea la primera arista
        Arista *anterior = aux_dos->primera_arista_;
        porBorrar = anterior->siguiente_arista_;

        while (porBorrar != nullptr) {
            if (porBorrar->adyacente_->nombre_nodo_ == aux_uno->nombre_nodo_) {
                anterior->siguiente_arista_ = porBorrar->siguiente_arista_;
                delete porBorrar;
                break;
            }

            anterior = anterior->siguiente_arista_;
            porBorrar = anterior->siguiente_arista_;
        }
    }
}

bool Grafica::buscarNodo(std::string nodo) const {
    Nodo *puntero = primer_nodo_;

    while (puntero != nullptr) {
        if (puntero->nombre_nodo_ == nodo) {
            return true;
        }
        puntero = puntero->siguiente_nodo_;
    }

    return false;
}

bool Grafica::buscarArista(std::string nodo1, std::string nodo2) const {
    Nodo *puntero = primer_nodo_;

    Nodo *aux_uno = nullptr;
    Nodo *aux_dos = nullptr;

    while (puntero != nullptr) {
        if (puntero->nombre_nodo_ == nodo1) {
            aux_uno = puntero;
        }
        if (puntero->nombre_nodo_ == nodo2) {
            aux_dos = puntero;
        }

        if (aux_uno != nullptr && aux_dos != nullptr) {
            break;
        }

        puntero = puntero->siguiente_nodo_;
    }

    if (aux_uno == nullptr || aux_dos == nullptr) {
        return false;
    }

    Arista *puntero_arista = aux_uno->primera_arista_;

    while (puntero_arista != nullptr) {
        if (puntero_arista->adyacente_ == aux_dos) {
            return true;
        }
        puntero_arista = puntero_arista->siguiente_arista_;
    }

    return false;
}

unsigned int Grafica::gradoNodo(std::string nodo) const {
    Nodo *puntero = primer_nodo_;

    while (puntero != nullptr) {
        if (puntero->nombre_nodo_ == nodo) {
            return puntero->grado_nodo_;
        }
        puntero = puntero->siguiente_nodo_;
    }

    std::cerr << "Error: No existe tal nodo.\n";
    return -1;
}

unsigned int Grafica::orden() const {
    return num_nodos_;
}

unsigned int Grafica::tamano() const {
    return num_aristas_;
}

void Grafica::vaciarNodo(std::string nodo) {
    Nodo *puntero = primer_nodo_;

    while (puntero != nullptr) {
        if (puntero->nombre_nodo_ == nodo) {
            while (puntero->primera_arista_ != nullptr) {
                eliminarArista(puntero->nombre_nodo_, puntero->primera_arista_->adyacente_->nombre_nodo_);
            }
            return;
        }

        puntero = puntero->siguiente_nodo_;
    }

    std::cerr << "Error: No se encontró el nodo.\n";
}

void Grafica::vaciarGrafica() {
    while (primer_nodo_ != nullptr) {
        eliminarNodo(primer_nodo_->nombre_nodo_);
    }
}

bool Grafica::estaVacia() const {
    return num_nodos_ == 0;
}

void Grafica::imprimir() const {
    Nodo *puntero = primer_nodo_;

    while (puntero != nullptr) {
        std::cout << puntero->nombre_nodo_ << ": ";

        Arista *puntero_arista = puntero->primera_arista_;
        while (puntero_arista != nullptr) {
            std::cout << puntero_arista->adyacente_->nombre_nodo_;

            if (puntero_arista->siguiente_arista_ != nullptr) {
                std::cout << ", ";
            }

            puntero_arista = puntero_arista->siguiente_arista_;
        }
        std::cout << '\n';

        puntero = puntero->siguiente_nodo_;
    }
}

//----------------------------------------------------------------------
// Nodo
//----------------------------------------------------------------------

Nodo::Nodo(std::string nombre, Nodo * siguiente /* = nullptr */) {
    nombre_nodo_ = nombre;
    grado_nodo_ = 0;
    primera_arista_ = nullptr;
    ultima_arista_ = nullptr;
    siguiente_nodo_ = siguiente;
}

//----------------------------------------------------------------------
// Arista
//----------------------------------------------------------------------

Arista::Arista(Nodo *adyacente, Arista *siguiente /* = nullptr */) {
    adyacente_ = adyacente;
    siguiente_arista_ = siguiente;
}

Nodo *buscarDireccion(std::string nodo, Nodo **previo);
