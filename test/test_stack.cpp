
#include <iostream>
#include "stack.hpp"

using namespace std;

void test_stack() {
    Stack* historial = stack_create();

    cout << "Pila vacia: "
         << stack_is_empty(historial) << endl;

    stack_push(historial, "PRESTAR 1001 50");
    stack_push(historial, "RESERVA 1002 50");
    stack_push(historial, "DEVOLVER 1001 50");

    cout << "Ultimas 2 operaciones:" << endl;
    stack_print_top(historial, 2);

    cout << "Operacion eliminada: "
         << stack_pop(historial) << endl;

    cout << "Historial restante:" << endl;
    stack_print_top(historial, 10);

    stack_destroy(historial);

}
