
#ifndef QUEUE_HPP
#define QUEUE_HPP

// TAD Cola (FIFO) de enteros, enlazada. Se usa para las reservas de cada libro.
struct Queue;

// Pre: ninguna
// Post: devuelve una cola vacía
Queue* queue_create();

// Pre: q != nullptr
// Post: agrega value al final de la cola. O(1)
void queue_enqueue(Queue* q, int value);

// Pre: q != nullptr y !queue_is_empty(q)
// Post: quita el primer elemento y lo devuelve. O(1)
int queue_dequeue(Queue* q);

// Pre: q != nullptr y !queue_is_empty(q)
// Post: devuelve el primer elemento sin quitarlo
int queue_front(const Queue* q);

// Pre: q != nullptr
// Post: true si la cola no tiene elementos
bool queue_is_empty(const Queue* q);

// Pre: q != nullptr
// Post: devuelve la cantidad de elementos. O(1)
int queue_size(const Queue* q);

// Pre: q != nullptr
// Post: true si value está en la cola
bool queue_contains(const Queue* q, int value);

// Pre: q != nullptr
// Post: imprime los valores del primero al último, separados por espacio
// (sin salto de línea al final)
void queue_print(const Queue* q);

// Pre: q != nullptr
// Post: libera todos los nodos y la cola
void queue_destroy(Queue* q);

#endif
