#ifndef CATALOG_HPP
#define CATALOG_HPP

#include <string>
#include "book.hpp"

// TAD Catalogo: arbol binario de busqueda (ABB) de libros ordenado por codigo.
// El catalogo es duenio de los libros que contiene: los libera al eliminarlos
// (catalog_remove) y al destruirse (catalog_destroy).
// En todas las operaciones, c debe venir de catalog_create() y no haber sido
// destruido.

struct Catalog;

// pre:  ninguna.
// post: devuelve un catalogo vacio (0 libros, altura 0).
Catalog *catalog_create();

// pre:  b != nullptr.
// post: si no habia un libro con el codigo de b, lo agrega, el catalogo pasa a
//       ser duenio de b y devuelve true. Si el codigo ya existia, no modifica
//       el catalogo, devuelve false y b sigue siendo responsabilidad de quien
//       llama.
bool catalog_insert(Catalog *c, Book *b); // false si el codigo ya existe

// pre:  ninguna.
// post: devuelve el libro con ese codigo, o nullptr si no existe. No modifica
//       el catalogo; el libro sigue perteneciendo al catalogo.
Book *catalog_find(const Catalog *c, int code); // nullptr si no existe

// pre:  ninguna.
// post: si existia un libro con ese codigo, lo saca del catalogo, lo libera
//       (book_destroy) y devuelve true; el resto de los libros sigue ordenado
//       por codigo. Si no existia, no modifica el catalogo y devuelve false.
bool catalog_remove(Catalog *c, int code); // libera el libro; false si no existe

// pre:  ninguna.
// post: imprime "CATALOGO:" y debajo una linea por libro, en orden creciente
//       de codigo (inorden): <cod> <titulo> <autor> <disponibles>/<total>.
//       No modifica el catalogo.
void catalog_print(const Catalog *c); // inorden

// pre:  ninguna.
// post: imprime "AUTOR <autor>:" y debajo una linea <cod> <titulo> por cada
//       libro de ese autor, en orden creciente de codigo. Si no hay ninguno,
//       imprime solo el encabezado. No modifica el catalogo.
void catalog_print_author(const Catalog *c, const std::string &author);

// pre:  ninguna.
// post: devuelve la cantidad de libros del catalogo. No lo modifica.
int catalog_count(const Catalog *c);

// pre:  ninguna.
// post: devuelve la altura del arbol, contando niveles: 0 si esta vacio y 1 si
//       tiene un solo libro. No modifica el catalogo.
int catalog_height(const Catalog *c);

// pre:  ninguna.
// post: libera todos los nodos, todos los libros y el propio catalogo. Despues
//       de llamarla, c no puede volver a usarse.
void catalog_destroy(Catalog *c); // libera arbol y libros

#endif
