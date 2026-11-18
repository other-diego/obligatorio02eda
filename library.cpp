#include "library.hpp"
#include "book.hpp"
#include "catalog.hpp"
#include "member.hpp"
#include "member_list.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include <iostream>
#include <string>

struct Library {
    Catalog* catalogo;
    MemberList* miembros;
    Stack* historial;
};

Library* library_create() {
    return new Library{
        catalog_create(),
        member_list_create(),
        stack_create()
    };
}

void library_destroy(Library* library) {
    catalog_destroy(library->catalogo);
    member_list_destroy(library->miembros);
    stack_destroy(library->historial);
    delete library;
}

void library_lend(Library* library, int numeroSocio, int codigoLibro) {
    Member* socio = member_list_find(library->miembros, numeroSocio);
    if (socio == nullptr) {
        std::cout << "ERROR: El socio " << numeroSocio << " es inexistente\n";
        return;
    }
    
    Book* libro = catalog_find(library->catalogo, codigoLibro);
    if (libro == nullptr) {
        std::cout << "ERROR: El libro " << codigoLibro << " es inexistente\n";
        return;
    }

    Queue* colaReservas = book_reservations(libro);

    if (member_has_loan(socio, codigoLibro) || queue_contains(colaReservas, numeroSocio)) {
        std::cout << "ERROR: El socio ya tiene prestado o reservado ese libro\n";
        return;
    }

    if (member_commitments(socio) >= 3) {
        std::cout << "ERROR: El socio ya tiene 3 compromisos\n";
        return;
    }

    const std::string datosHistorial = std::to_string(numeroSocio) + " " + std::to_string(codigoLibro);

    if (book_lend(libro)) {
        member_add_loan(socio, codigoLibro);
        stack_push(library->historial, "PRESTAR " + datosHistorial);
        
        std::cout << "OK prestamo " << codigoLibro
          << " a socio " << numeroSocio << '\n';
        return;
    }

    queue_enqueue(colaReservas, numeroSocio);
    member_add_reservation(socio);
    stack_push(library->historial, "RESERVA " + datosHistorial);

    std::cout << "OK reserva " << codigoLibro
          << " para socio " << numeroSocio
          << " (posicion " << queue_size(colaReservas) << ")\n";
}

void library_give_back(Library* library, int numeroSocio, int codigoLibro) {
    Member* socio = member_list_find(library->miembros, numeroSocio);
    if (socio == nullptr) {
        std::cout << "ERROR socio " << numeroSocio << " inexistente\n";
        return;
    }

    Book* libro = catalog_find(library->catalogo, codigoLibro);
    if (libro == nullptr) {
        std::cout << "ERROR libro " << codigoLibro << " inexistente\n";
        return;
    }

    if (!member_remove_loan(socio, codigoLibro)) {
        std::cout << "ERROR el socio no tiene prestado ese libro\n";
        return;
    }

    book_give_back(libro);

    const std::string code = std::to_string(codigoLibro);
    stack_push(library->historial, "DEVOLVER " + std::to_string(numeroSocio) + " " + code);

    Queue* colaReservas = book_reservations(libro);

    std::cout << "OK devolucion " << codigoLibro << " de socio " << numeroSocio;

    if (!queue_is_empty(colaReservas)) {
        const int nroSiguiente = queue_dequeue(colaReservas);
        Member* siguienteSocio = member_list_find(library->miembros, nroSiguiente);

        member_remove_reservation(siguienteSocio);
        member_add_loan(siguienteSocio, codigoLibro);
        book_lend(libro);

        stack_push(library->historial, "PRESTAR " + std::to_string(nroSiguiente) + " " + code);
        std::cout << "; prestado a socio " << nroSiguiente << " por reserva";
    }
    
    std::cout << '\n';
}