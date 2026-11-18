#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>

// Biblioteca: coordina catálogo, socios, préstamos, reservas e historial.
// Cada operación imprime su resultado con el formato de la letra
// ("OK ..." o una línea que empieza con "ERROR").
struct Library;

// Pre: ninguna
// Post: devuelve una biblioteca vacía
Library* library_create();

// Pre: library apunta a una biblioteca válida
// Post: si cod > 0, ejemplares >= 1 y el código no existe, agrega el libro e
// imprime "OK libro <cod> agregado"; si no, imprime ERROR y no cambia nada
void library_add_book(Library* library, int codigoLibro, int ejemplares,
                      const std::string& titulo, const std::string& autor);

// Pre: library apunta a una biblioteca válida
// Post: si el libro existe y no tiene préstamos activos ni reservas, lo elimina
// (liberando su memoria) e imprime "OK libro <cod> eliminado"; si no, ERROR
void library_remove_book(Library* library, int codigoLibro);

// Pre: library apunta a una biblioteca válida
// Post: imprime "<cod> <titulo> <autor> <disponibles>/<total>" y la línea
// "RESERVAS: ..." (o "RESERVAS: vacia"); si el libro no existe, ERROR
void library_show_book(const Library* library, int codigoLibro);

// Pre: library apunta a una biblioteca válida
// Post: imprime "CATALOGO:" y una línea por libro, ordenado por código
void library_print_catalog(const Library* library);

// Pre: library apunta a una biblioteca válida
// Post: imprime "AUTOR <autor>:" y los libros de ese autor ordenados por código
void library_print_author(const Library* library, const std::string& autor);

// Pre: library apunta a una biblioteca válida
// Post: si num > 0 y el número no existe, registra el socio e imprime
// "OK socio <num> agregado"; si no, imprime ERROR y no cambia nada
void library_add_member(Library* library, int numeroSocio, const std::string& nombre);

// Pre: library apunta a una biblioteca válida
// Post: si el socio existe y no tiene préstamos ni reservas, lo elimina
// (liberando su memoria) e imprime "OK socio <num> eliminado"; si no, ERROR
void library_remove_member(Library* library, int numeroSocio);

// Pre: library apunta a una biblioteca válida
// Post: imprime "SOCIOS:" y una línea por socio, ordenado por número
void library_print_members(const Library* library);

// Pre: library apunta a una biblioteca válida
// Post: presta o reserva el libro y registra en el historial
// Si el pedido se rechaza, muestra error y conserva los datos
void library_lend(Library* library, int numeroSocio, int codigoLibro);

// Pre: library apunta a una biblioteca válida
// Post: registra la devolución y presta el ejemplar al primero de la cola si hay una reserva pendiente
// Registra los movimientos en el historial
// Si el pedido se rechaza, muestra error y conserva los datos
void library_give_back(Library* library, int numeroSocio, int codigoLibro);

// Pre: library apunta a una biblioteca válida
// Post: si n >= 0, imprime "HISTORIAL:" y las últimas n operaciones (todas si
// hay menos), de la más reciente a la más antigua; si n < 0, ERROR
void library_print_history(const Library* library, int n);

// Pre: library apunta a una biblioteca válida
// Post: imprime "ESTADISTICAS: libros=<l> altura=<h> socios=<s> prestamos=<p> reservas=<r>"
void library_print_stats(const Library* library);

// Pre: library apunta a una biblioteca creada que todavía no fue destruida
// Post: libera el catálogo, la lista de socios, el historial y la biblioteca
void library_destroy(Library* library);

#endif
