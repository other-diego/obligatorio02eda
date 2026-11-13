
#include "stack.hpp"
#include <iostream>

using namespace std;

struct NodoPila {
    string dato;
    NodoPila* siguiente;
};

struct Stack {
    NodoPila* tope;
};


Stack* stack_create() {
    Stack* s = new Stack;

    s->tope = nullptr;

    return s;
}


bool stack_is_empty(const Stack* s) {
    return s->tope == nullptr;
}


void stack_push(Stack* s, const string& value) {
    NodoPila* nuevo = new NodoPila;

    nuevo->dato = value;
    nuevo->siguiente = s->tope;

    s->tope = nuevo;
}


string stack_pop(Stack* s) {
    NodoPila* auxiliar = s->tope;

    string valor = auxiliar->dato;

    s->tope = auxiliar->siguiente;

    delete auxiliar;

    return valor;
}


void stack_print_top(const Stack* s, int n) {
    NodoPila* actual = s->tope;
    int contador = 0;

    while (actual != nullptr && contador < n) {
        cout << actual->dato << endl;

        actual = actual->siguiente;
        contador++;
    }
}


void stack_destroy(Stack* s) {
    while (!stack_is_empty(s)) {
        stack_pop(s);
    }

    delete s;
}
