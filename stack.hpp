
#ifndef STACK_HPP
#define STACK_HPP

#include <string>

// TAD Pila (LIFO) de cadenas, enlazada. Se usa para el historial de operaciones.
struct Stack;

// Pre: ninguna
// Post: devuelve una pila vacía
Stack* stack_create();

// Pre: s != nullptr
// Post: apila value en el tope. O(1)
void stack_push(Stack* s, const std::string& value);

// Pre: s != nullptr y !stack_is_empty(s)
// Post: quita el tope y lo devuelve. O(1)
std::string stack_pop(Stack* s);

// Pre: s != nullptr
// Post: true si la pila no tiene elementos
bool stack_is_empty(const Stack* s);

// Pre: s != nullptr
// Post: imprime los n elementos más recientes (todos si hay menos), uno por
// línea, del tope hacia abajo, sin modificar la pila
void stack_print_top(const Stack* s, int n);

// Pre: s != nullptr
// Post: libera todos los nodos y la pila
void stack_destroy(Stack* s);

#endif
