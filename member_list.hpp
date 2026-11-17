#ifndef MEMBER_LIST_HPP
#define MEMBER_LIST_HPP

#include "member.hpp"

struct MemberList;

// post: devuelve una lista vacia
MemberList *member_list_create();

// pre: list != nullptr, m != nullptr
// post: inserta el socio manteniendo el orden por numero. Devuelve false si ya existe el numero.
bool member_list_insert(MemberList *list, Member *m);

// pre: list != nullptr
// post: devuelve el socio con ese numero o nullptr si no existe
Member *member_list_find(const MemberList *list, int num);

// pre: list != nullptr
// post: si existe el socio, lo elimina y devuelve true, sino false
bool member_list_remove(MemberList *list, int num);

// pre: list != nullptr
// post: devuelve la cantidad de socios
int member_list_count(const MemberList *list);

// pre: list != nullptr
// post: imprime los socios ordenados por numero
void member_list_print(const MemberList *list);

// pre: list != nullptr
// post: libera todos los nodos y socios
void member_list_destroy(MemberList *list);

#endif