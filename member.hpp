#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <string>

struct Member;

// pre: num > 0
// post: devuelve un socio nuevo sin prestamos ni reservas
Member *member_create(int num, const std::string &name);

// pre: m != nullptr
// post: devuelve el numero del socio
int member_number(const Member *m);

// pre: m != nullptr
// post: devuelve el nombre del socio
std::string member_name(const Member *m);

// pre: m != nullptr
// post: true si el socio tiene prestado el libro con ese codigo
bool member_has_loan(const Member *m, int code);

// pre: m != nullptr
// post: agrega el codigo a los prestamos del socio
void member_add_loan(Member *m, int code);

// pre: m != nullptr
// post: si el codigo estaba, lo elimina y devuelve true; si no, false
bool member_remove_loan(Member *m, int code);

// pre: m != nullptr
// post: cantidad de prestamos activos
int member_loans(const Member *m);

// pre: m != nullptr
// post: cantidad de reservas en espera
int member_reservations(const Member *m);

// pre: m != nullptr
// post: incrementa las reservas del socio
void member_add_reservation(Member *m);

// pre: m != nullptr y member_reservations(m) > 0
// post: decrementa las reservas del socio
void member_remove_reservation(Member *m);

// pre: m != nullptr
// post: devuelve prestamos + reservas
int member_commitments(const Member *m);

// pre: m != nullptr
// post: libera el socio y su lista de prestamos
void member_destroy(Member *m);

#endif