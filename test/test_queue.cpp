
#include <iostream>
#include "queue.hpp"

using namespace std;

void test_queue() {
    Queue* cola = queue_create();

    cout << "Cola vacia: " << queue_is_empty(cola) << endl;

    queue_enqueue(cola, 1001);
    queue_enqueue(cola, 1002);
    queue_enqueue(cola, 1003);

    cout << "Cola: ";
    queue_print(cola);
    cout << endl;

    cout << "Cantidad: " << queue_size(cola) << endl;
    cout << "Primero: " << queue_front(cola) << endl;

    cout << "Existe 1002: "
         << queue_contains(cola, 1002) << endl;

    cout << "Sale: " << queue_dequeue(cola) << endl;

    cout << "Cola restante: ";
    queue_print(cola);
    cout << endl;

    queue_destroy(cola);

}
