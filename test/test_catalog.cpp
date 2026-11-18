#include <iostream>
#include "catalog.hpp"

using namespace std;

void test_catalog() {

    Catalog* c = catalog_create();

    // Insertar
    cout << "Insertar 50: " << catalog_insert(c, book_create(50, 2, "Ficciones", "Borges")) << endl; // esperado 1
    cout << "Insertar 30: " << catalog_insert(c, book_create(30, 1, "Rayuela", "Cortazar")) << endl; // esperado 1
    cout << "Insertar 70: " << catalog_insert(c, book_create(70, 3, "El Aleph", "Borges"))  << endl; // esperado 1

    Book* repetido = book_create(30, 1, "Otro", "Otro");
    cout << "Insertar 30 repetido: " << catalog_insert(c, repetido) << endl; // esperado 0
    book_destroy(repetido);

    cout << "Cantidad: " << catalog_count(c)  << endl; // esperado 3
    cout << "Altura: "   << catalog_height(c) << endl; // esperado 2

    // Buscar
    Book* encontrado = catalog_find(c, 70);
    cout << "Buscar 70: " << (encontrado != nullptr ? book_title(encontrado) : "no existe") << endl; // El Aleph
    cout << "Buscar 99: " << (catalog_find(c, 99) != nullptr ? "existe" : "no existe") << endl;      // no existe

    catalog_print(c);                  // esperado 30, 50, 70
    catalog_print_author(c, "Borges"); // esperado 50, 70

    // Borrar
    catalog_insert(c, book_create(60, 1, "Sobre heroes y tumbas", "Sabato"));
    catalog_insert(c, book_create(80, 2, "El tunel", "Sabato"));
    catalog_insert(c, book_create(65, 1, "El hacedor", "Borges"));
    cout << "Cantidad: " << catalog_count(c)  << endl; // esperado 6
    cout << "Altura: "   << catalog_height(c) << endl; // esperado 4

    cout << "Borrar 99: " << catalog_remove(c, 99) << endl; // esperado 0 (no existe)
    cout << "Borrar 50: " << catalog_remove(c, 50) << endl; // esperado 1 (dos hijos)
    cout << "Altura: "    << catalog_height(c)     << endl; // esperado 3
    catalog_print(c);                                       // esperado 30, 60, 65, 70, 80

    cout << "Borrar 30: " << catalog_remove(c, 30) << endl; // esperado 1 (hoja)
    cout << "Borrar 30: " << catalog_remove(c, 30) << endl; // esperado 0 (ya no esta)
    cout << "Borrar 70: " << catalog_remove(c, 70) << endl; // esperado 1 (dos hijos)
    cout << "Borrar 60: " << catalog_remove(c, 60) << endl; // esperado 1 (un hijo)
    catalog_print(c);                                       // esperado 65, 80

    cout << "Borrar 80: " << catalog_remove(c, 80) << endl; // esperado 1
    cout << "Borrar 65: " << catalog_remove(c, 65) << endl; // esperado 1
    cout << "Cantidad: "  << catalog_count(c)      << endl; // esperado 0
    cout << "Altura: "    << catalog_height(c)     << endl; // esperado 0
    cout << "Borrar 65: " << catalog_remove(c, 65) << endl; // esperado 0 (vacio)

    // Destruir (revisar fugas con: leaks --atExit -- ./test_catalog)
    catalog_insert(c, book_create(10, 1, "Martin Fierro", "Hernandez"));
    catalog_destroy(c);

    Catalog* vacio = catalog_create();
    catalog_destroy(vacio);

    Catalog* grande = catalog_create();
    int codigos[] = {50, 30, 70, 20, 40, 60, 80, 90};
    for (int k : codigos) {
        catalog_insert(grande, book_create(k, 1, "Titulo", "Autor"));
    }
    catalog_destroy(grande);

    cout << "Fin" << endl;
}
