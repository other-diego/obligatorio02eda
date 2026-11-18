#ifndef LIBRARY_HPP
#define LIBRARY_HPP

struct Library;

// Pre: ninguna
// Post: devuelve una biblioteca vacía
Library* library_create();

// Pre: library apunta a una biblioteca válida
// Post: presta o reserva el libro y registra en el historial
// Si el pedido se rechaza, muestra error y conserva los datos
void library_lend(Library* library, int numeroSocio, int codigoLibro);

// Pre: library apunta a una biblioteca válida
// Post: registra la devolución y presta el ejemplar al primero de la cola si hay una reserva pendiente 
// Registra los movimientos en el historial
// Si el pedido se rechaza, muestra error y conserva los datos
void library_give_back(Library* library, int numeroSocio, int codigoLibro);

// Pre: library apunta a una biblioteca creada que todavía no fue destruida
// Post: libera el catálogo, la lista de socios, el historial y la biblioteca
void library_destroy(Library* library);

#endif