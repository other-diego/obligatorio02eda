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
    int prestamos;  // préstamos activos en total (para ESTADISTICAS en O(1))
    int reservas;   // reservas en espera en total
};

Library* library_create() {
    return new Library{
        catalog_create(),
        member_list_create(),
        stack_create(),
        0,
        0
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
        std::cout << "ERROR socio " << numeroSocio << " inexistente\n";
        return;
    }
    
    Book* libro = catalog_find(library->catalogo, codigoLibro);
    if (libro == nullptr) {
        std::cout << "ERROR libro " << codigoLibro << " inexistente\n";
        return;
    }

    Queue* colaReservas = book_reservations(libro);

    if (member_has_loan(socio, codigoLibro) || queue_contains(colaReservas, numeroSocio)) {
        std::cout << "ERROR el socio ya tiene prestado o reservado ese libro\n";
        return;
    }

    if (member_commitments(socio) >= 3) {
        std::cout << "ERROR el socio ya tiene 3 compromisos\n";
        return;
    }

    const std::string datosHistorial = std::to_string(numeroSocio) + " " + std::to_string(codigoLibro);

    if (book_lend(libro)) {
        member_add_loan(socio, codigoLibro);
        library->prestamos++;
        stack_push(library->historial, "PRESTAR " + datosHistorial);
        
        std::cout << "OK prestamo " << codigoLibro
          << " a socio " << numeroSocio << '\n';
        return;
    }

    queue_enqueue(colaReservas, numeroSocio);
    member_add_reservation(socio);
    library->reservas++;
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
    library->prestamos--;

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
        library->reservas--;
        library->prestamos++;

        stack_push(library->historial, "PRESTAR " + std::to_string(nroSiguiente) + " " + code);
        std::cout << "; prestado a socio " << nroSiguiente << " por reserva";
    }
    
    std::cout << '\n';
}

void library_add_book(Library* library, int codigoLibro, int ejemplares,
                      const std::string& titulo, const std::string& autor) {
    if (codigoLibro <= 0 || ejemplares < 1) {
        std::cout << "ERROR codigo o cantidad de ejemplares invalidos\n";
        return;
    }

    if (catalog_find(library->catalogo, codigoLibro) != nullptr) {
        std::cout << "ERROR libro " << codigoLibro << " ya existe\n";
        return;
    }

    catalog_insert(library->catalogo, book_create(codigoLibro, ejemplares, titulo, autor));
    std::cout << "OK libro " << codigoLibro << " agregado\n";
}

void library_remove_book(Library* library, int codigoLibro) {
    Book* libro = catalog_find(library->catalogo, codigoLibro);
    if (libro == nullptr) {
        std::cout << "ERROR libro " << codigoLibro << " inexistente\n";
        return;
    }

    if (book_available(libro) < book_total(libro) || !queue_is_empty(book_reservations(libro))) {
        std::cout << "ERROR el libro " << codigoLibro << " tiene prestamos o reservas\n";
        return;
    }

    catalog_remove(library->catalogo, codigoLibro);
    std::cout << "OK libro " << codigoLibro << " eliminado\n";
}

void library_show_book(const Library* library, int codigoLibro) {
    Book* libro = catalog_find(library->catalogo, codigoLibro);
    if (libro == nullptr) {
        std::cout << "ERROR libro " << codigoLibro << " inexistente\n";
        return;
    }

    std::cout << book_code(libro) << " " << book_title(libro) << " " << book_author(libro)
              << " " << book_available(libro) << "/" << book_total(libro) << '\n';

    Queue* colaReservas = book_reservations(libro);
    std::cout << "RESERVAS: ";
    if (queue_is_empty(colaReservas)) {
        std::cout << "vacia";
    } else {
        queue_print(colaReservas);
    }
    std::cout << '\n';
}

void library_print_catalog(const Library* library) {
    catalog_print(library->catalogo);
}

void library_print_author(const Library* library, const std::string& autor) {
    catalog_print_author(library->catalogo, autor);
}

void library_add_member(Library* library, int numeroSocio, const std::string& nombre) {
    if (numeroSocio <= 0) {
        std::cout << "ERROR numero de socio invalido\n";
        return;
    }

    if (member_list_find(library->miembros, numeroSocio) != nullptr) {
        std::cout << "ERROR socio " << numeroSocio << " ya existe\n";
        return;
    }

    member_list_insert(library->miembros, member_create(numeroSocio, nombre));
    std::cout << "OK socio " << numeroSocio << " agregado\n";
}

void library_remove_member(Library* library, int numeroSocio) {
    Member* socio = member_list_find(library->miembros, numeroSocio);
    if (socio == nullptr) {
        std::cout << "ERROR socio " << numeroSocio << " inexistente\n";
        return;
    }

    if (member_commitments(socio) > 0) {
        std::cout << "ERROR el socio " << numeroSocio << " tiene prestamos o reservas\n";
        return;
    }

    member_list_remove(library->miembros, numeroSocio);
    std::cout << "OK socio " << numeroSocio << " eliminado\n";
}

void library_print_members(const Library* library) {
    member_list_print(library->miembros);
}

void library_print_history(const Library* library, int n) {
    if (n < 0) {
        std::cout << "ERROR la cantidad de operaciones no puede ser negativa\n";
        return;
    }

    std::cout << "HISTORIAL:\n";
    stack_print_top(library->historial, n);
}

void library_print_stats(const Library* library) {
    std::cout << "ESTADISTICAS: libros=" << catalog_count(library->catalogo)
              << " altura=" << catalog_height(library->catalogo)
              << " socios=" << member_list_count(library->miembros)
              << " prestamos=" << library->prestamos
              << " reservas=" << library->reservas << '\n';
}
