
#include <iostream>
#include "book.hpp"
#include "queue.hpp"

using namespace std;

void test_book() {
    // Crear un libro con 2 ejemplares
    Book* libro = book_create(50, 2, "Ficciones", "Borges");

    cout << "Codigo: " << book_code(libro) << endl;
    cout << "Titulo: " << book_title(libro) << endl;
    cout << "Autor: " << book_author(libro) << endl;
    cout << "Total: " << book_total(libro) << endl;
    cout << "Disponibles: " << book_available(libro) << endl;

    // Prestar ejemplares
    cout << "Prestamo 1: " << book_lend(libro) << endl;
    cout << "Prestamo 2: " << book_lend(libro) << endl;
    cout << "Prestamo 3: " << book_lend(libro) << endl;

    cout << "Disponibles: " << book_available(libro) << endl;

    // Agregar reservas
    Queue* reservas = book_reservations(libro);

    queue_enqueue(reservas, 1001);
    queue_enqueue(reservas, 1002);

    cout << "Reservas: ";
    queue_print(reservas);
    cout << endl;

    // Devolver un ejemplar
    book_give_back(libro);

    cout << "Disponibles despues de devolver: "
         << book_available(libro) << endl;

    // Liberar memoria
    book_destroy(libro);

}
