
#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include "queue.hpp"

// TAD Libro: datos del libro, ejemplares disponibles y su cola de reservas.
struct Book;

// Pre: code > 0, copies >= 1
// Post: devuelve un libro con copies ejemplares disponibles y una cola de
// reservas vacía
Book* book_create(int code, int copies,
                  const std::string& title,
                  const std::string& author);

// Pre: b != nullptr
// Post: devuelve el código del libro
int book_code(const Book* b);

// Pre: b != nullptr
// Post: devuelve el título del libro
std::string book_title(const Book* b);

// Pre: b != nullptr
// Post: devuelve el autor del libro
std::string book_author(const Book* b);

// Pre: b != nullptr
// Post: devuelve la cantidad de ejemplares disponibles
int book_available(const Book* b);

// Pre: b != nullptr
// Post: devuelve la cantidad total de ejemplares
int book_total(const Book* b);

// Pre: b != nullptr
// Post: devuelve la cola de reservas del libro (sigue siendo del libro)
Queue* book_reservations(Book* b);

// Pre: b != nullptr
// Post: si hay ejemplares disponibles, descuenta uno y devuelve true;
// si no, devuelve false sin cambiar nada
bool book_lend(Book* b);

// Pre: b != nullptr y book_available(b) < book_total(b)
// Post: suma un ejemplar disponible
void book_give_back(Book* b);

// Pre: b != nullptr
// Post: libera el libro y también su cola de reservas
void book_destroy(Book* b);

#endif
