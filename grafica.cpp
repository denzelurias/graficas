//
// Created by denze on 4/7/2026.
//

#include "grafica.h"

#include <iostream>

namespace {

Nodo *buscarNodoPtr(Nodo *primer_nodo, const std::string &nombre) {
    Nodo *puntero = primer_nodo;

    while (puntero != nullptr) {
        if (puntero->nombre_nodo_ == nombre) {
            return puntero;
        }
        puntero = puntero->siguiente_nodo_;
    }

    return nullptr;
}

const Nodo *buscarNodoPtr(const Nodo *primer_nodo, const std::string &nombre) {
    const Nodo *puntero = primer_nodo;

    while (puntero != nullptr) {
        if (puntero->nombre_nodo_ == nombre) {
            return puntero;
        }
        puntero = puntero->siguiente_nodo_;
    }

    return nullptr;
}

void enlazarArista(Nodo *origen, Arista *nueva_arista) {
    if (origen->ultima_arista_ == nullptr) {
        origen->primera_arista_ = nueva_arista;
        origen->ultima_arista_ = nueva_arista;
        return;
    }

    origen->ultima_arista_->siguiente_arista_ = nueva_arista;
    origen->ultima_arista_ = nueva_arista;
}

bool eliminarPrimeraAristaHacia(Nodo *origen, Nodo *destino) {
    if (origen->primera_arista_ == nullptr) {
        return false;
    }

    if (origen->primera_arista_->adyacente_ == destino) {
        Arista *por_borrar = origen->primera_arista_;
        origen->primera_arista_ = por_borrar->siguiente_arista_;

        if (origen->ultima_arista_ == por_borrar) {
            origen->ultima_arista_ = nullptr;
        }

        delete por_borrar;
        return true;
    }

    Arista *anterior = origen->primera_arista_;
    Arista *actual = anterior->siguiente_arista_;

    while (actual != nullptr) {
        if (actual->adyacente_ == destino) {
            anterior->siguiente_arista_ = actual->siguiente_arista_;

            if (origen->ultima_arista_ == actual) {
                origen->ultima_arista_ = anterior;
            }

            delete actual;
            return true;
        }

        anterior = actual;
        actual = actual->siguiente_arista_;
    }

    return false;
}

}  // namespace

//----------------------------------------------------------------------
// Grafica
//----------------------------------------------------------------------

Grafica::Grafica()
        : num_nodos_{0},
        num_aristas_{0},
        primer_nodo_{nullptr},
        ultimo_nodo_{nullptr} {}

Grafica::Grafica(const Grafica &graf) : num_nodos_{0}, num_aristas_{0},
      primer_nodo_{nullptr}, ultimo_nodo_{nullptr}{
    *this = graf;
}

Grafica::~Grafica() {
    vaciarGrafica();
}

Grafica& Grafica::operator=(const Grafica &graf) {
    if (this == &graf) return *this;
    vaciarGrafica();

    Nodo *puntero = graf.primer_nodo_;
    while (puntero !=nullptr) {
        agregarNodo(puntero->nombre_nodo_);

        puntero = puntero->siguiente_nodo_;
    }

    puntero = graf.primer_nodo_;
    while (puntero !=nullptr) {
        Arista * puntero_arista = puntero->primera_arista_;
        while (puntero_arista != nullptr) {
            if (!buscarArista(puntero->nombre_nodo_, puntero_arista->adyacente_->nombre_nodo_)) {
                agregarArista(puntero->nombre_nodo_, puntero_arista->adyacente_->nombre_nodo_);
            }

            puntero_arista = puntero_arista->siguiente_arista_;
        }

        puntero = puntero->siguiente_nodo_;
    }

    return *this;
}

void Grafica::agregarNodo(const std::string &nombre) {
    if (buscarNodo(nombre)) {
        return;
    }
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

void Grafica::agregarArista(const std::string &nodo1, const std::string &nodo2) {
    if (buscarArista(nodo1, nodo2)) {
        return;
    }

    Nodo *aux_uno = buscarNodoPtr(primer_nodo_, nodo1);
    Nodo *aux_dos = buscarNodoPtr(primer_nodo_, nodo2);

    if (aux_uno == nullptr || aux_dos == nullptr) {
        return;
    }

    Arista *nueva_arista = nullptr;
    Arista *nueva_arista_dos = nullptr;

    try {
        nueva_arista = new Arista(aux_dos);
        nueva_arista_dos = new Arista(aux_uno);
    } catch (const std::bad_alloc &mensaje) {
        delete nueva_arista;
        delete nueva_arista_dos;
        std::cerr << "Error de memoria: " << mensaje.what() << '\n';
        return;
    }

    if (aux_uno == aux_dos) {
        enlazarArista(aux_uno, nueva_arista);
        enlazarArista(aux_uno, nueva_arista_dos);
        ++num_aristas_;
        aux_uno->grado_nodo_ += 2;
        return;
    }

    enlazarArista(aux_uno, nueva_arista);
    enlazarArista(aux_dos, nueva_arista_dos);

    ++num_aristas_;
    ++aux_uno->grado_nodo_;
    ++aux_dos->grado_nodo_;
}

void Grafica::eliminarNodo(const std::string &nombre) {
    if (estaVacia()) {
        return;
    }

    Nodo *puntero = primer_nodo_;

    // En el caso que eliminemos el primer nodo
    if (puntero->nombre_nodo_ == nombre) {
        while (primer_nodo_->primera_arista_ != nullptr) {
            eliminarArista(primer_nodo_->nombre_nodo_, primer_nodo_->primera_arista_->adyacente_->nombre_nodo_);
        }

        if (primer_nodo_ == ultimo_nodo_) {
            ultimo_nodo_ = nullptr;
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
            return;
        }

        while (porBorrar->primera_arista_ != nullptr) {
            eliminarArista(porBorrar->nombre_nodo_, porBorrar->primera_arista_->adyacente_->nombre_nodo_);
        }

        puntero->siguiente_nodo_ = porBorrar->siguiente_nodo_;

        if (porBorrar == ultimo_nodo_) {
            ultimo_nodo_ = puntero;
        }

        delete porBorrar;

        --num_nodos_;
    }
}

void Grafica::eliminarArista(const std::string &nodo1, const std::string &nodo2) {
    if (!buscarArista(nodo1, nodo2)) {
        return;
    }

    Nodo *aux_uno = buscarNodoPtr(primer_nodo_, nodo1);
    Nodo *aux_dos = buscarNodoPtr(primer_nodo_, nodo2);

    if (aux_uno == nullptr || aux_dos == nullptr) {
        return;
    }

    if (aux_uno == aux_dos) {
        if (!eliminarPrimeraAristaHacia(aux_uno, aux_dos)) {
            return;
        }

        if (!eliminarPrimeraAristaHacia(aux_uno, aux_dos)) {
            return;
        }

        --num_aristas_;
        aux_uno->grado_nodo_ -= 2;
        return;
    }

    if (!eliminarPrimeraAristaHacia(aux_uno, aux_dos)) {
        return;
    }

    if (!eliminarPrimeraAristaHacia(aux_dos, aux_uno)) {
        return;
    }

    --num_aristas_;
    --aux_uno->grado_nodo_;
    --aux_dos->grado_nodo_;
}

bool Grafica::buscarNodo(const std::string &nodo) const {
    return buscarNodoPtr(static_cast<const Nodo *>(primer_nodo_), nodo) != nullptr;
}

bool Grafica::buscarArista(const std::string &nodo1, const std::string &nodo2) const {
    const Nodo *aux_uno = buscarNodoPtr(static_cast<const Nodo *>(primer_nodo_), nodo1);
    const Nodo *aux_dos = buscarNodoPtr(static_cast<const Nodo *>(primer_nodo_), nodo2);

    if (aux_uno == nullptr || aux_dos == nullptr) {
        return false;
    }

    const Arista *puntero_arista = aux_uno->primera_arista_;

    while (puntero_arista != nullptr) {
        if (puntero_arista->adyacente_ == aux_dos) {
            return true;
        }
        puntero_arista = puntero_arista->siguiente_arista_;
    }

    return false;
}

int Grafica::gradoNodo(const std::string &nodo) const {
    const Nodo *puntero = buscarNodoPtr(static_cast<const Nodo *>(primer_nodo_), nodo);

    if (puntero != nullptr) {
        return static_cast<int>(puntero->grado_nodo_);
    }

    return -1;
}

unsigned int Grafica::orden() const {
    return num_nodos_;
}

unsigned int Grafica::tamano() const {
    return num_aristas_;
}

void Grafica::vaciarNodo(const std::string &nodo) {
    Nodo *puntero = buscarNodoPtr(primer_nodo_, nodo);

    if (puntero == nullptr) {
        return;
    }

    while (puntero->primera_arista_ != nullptr) {
        eliminarArista(puntero->nombre_nodo_, puntero->primera_arista_->adyacente_->nombre_nodo_);
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
        bool primera_salida = true;
        bool lazo_impreso = false;

        while (puntero_arista != nullptr) {
            const bool es_lazo = puntero_arista->adyacente_ == puntero;

            if (!es_lazo || !lazo_impreso) {
                if (!primera_salida) {
                    std::cout << ", ";
                }

                std::cout << puntero_arista->adyacente_->nombre_nodo_;
                primera_salida = false;
            }

            if (es_lazo) {
                lazo_impreso = true;
            }

            puntero_arista = puntero_arista->siguiente_arista_;
        }
        std::cout << '\n';

        puntero = puntero->siguiente_nodo_;
    }
}

void Grafica::vaciarGrafica() {
    while (primer_nodo_ != nullptr) {
        eliminarNodo(primer_nodo_->nombre_nodo_);
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
