
#include "queue.hpp"
#include <iostream>

using namespace std;

struct NodoCola {
    int dato;
    NodoCola* siguiente;
};

struct Queue {
    NodoCola* primero;
    NodoCola* ultimo;
    int cantidad;
};


Queue* queue_create() {
    Queue* q = new Queue;

    q->primero = nullptr;
    q->ultimo = nullptr;
    q->cantidad = 0;

    return q;
}


bool queue_is_empty(const Queue* q) {
    return q->primero == nullptr;
}


void queue_enqueue(Queue* q, int value) {
    NodoCola* nuevo = new NodoCola;

    nuevo->dato = value;
    nuevo->siguiente = nullptr;

    if (q->primero == nullptr) {
        q->primero = nuevo;
        q->ultimo = nuevo;
    } else {
        q->ultimo->siguiente = nuevo;
        q->ultimo = nuevo;
    }

    q->cantidad++;
}


int queue_dequeue(Queue* q) {
    NodoCola* auxiliar = q->primero;

    int valor = auxiliar->dato;

    q->primero = auxiliar->siguiente;

    if (q->primero == nullptr) {
        q->ultimo = nullptr;
    }

    delete auxiliar;

    q->cantidad--;

    return valor;
}


int queue_front(const Queue* q) {
    return q->primero->dato;
}


int queue_size(const Queue* q) {
    return q->cantidad;
}


bool queue_contains(const Queue* q, int value) {
    NodoCola* actual = q->primero;

    while (actual != nullptr) {
        if (actual->dato == value) {
            return true;
        }

        actual = actual->siguiente;
    }

    return false;
}


void queue_print(const Queue* q) {
    NodoCola* actual = q->primero;

    while (actual != nullptr) {
        cout << actual->dato;

        if (actual->siguiente != nullptr) {
            cout << " ";
        }

        actual = actual->siguiente;
    }
}


void queue_destroy(Queue* q) {
    while (!queue_is_empty(q)) {
        queue_dequeue(q);
    }

    delete q;
}

