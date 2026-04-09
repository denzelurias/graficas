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
    }
    catch (const std::bad_alloc &mensaje) {
        std::cerr << "Error de memoria: " << mensaje.what() << '\n';
    }
}

void Grafica::eliminarNodo(std::string nombre) {
    Nodo *puntero = primer_nodo_;
    Nodo *porBorrar = puntero->siguiente_nodo_;

    // En el caso que eliminemos el primer nodo
    if (puntero->nombre_nodo_ == nombre) {
        while (primer_nodo_->primera_arista_ != nullptr) {
            eliminarArista(primer_nodo_->nombre_nodo_, primer_nodo_->primera_arista_->adyacente_->nombre_nodo_);
        }
    }
    else {
        while (porBorrar != nullptr) {
            if (puntero->nombre_nodo_ == nombre) {
                break;
            }

            if (porBorrar ==)

            puntero = puntero->siguiente_nodo_;
            porBorrar = porBorrar->siguiente_nodo_;
        }
    }
}

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

bool Grafica::estaVacia() const {
    return num_nodos_ == 0;
}

//----------------------------------------------------------------------
// Arista
//----------------------------------------------------------------------

Arista::Arista(Nodo *adyacente, Arista *siguiente /* = nullptr */) {
    adyacente_ = adyacente;
    siguiente_arista_ = siguiente;
}
