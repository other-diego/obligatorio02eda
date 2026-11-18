#include "library.cpp"

void test_library() {
    Library* biblioteca = library_create();
    
    Book* libro = book_create(50, 1, "Ficciones", "Borges");
    catalog_insert(biblioteca->catalogo, libro);

    member_list_insert(biblioteca->miembros, member_create(1001, "Bruno"));
    member_list_insert(biblioteca->miembros, member_create(1002, "Ana"));
    member_list_insert(biblioteca->miembros, member_create(1003, "Eva"));

    library_lend(biblioteca, 1001, 50);
    library_lend(biblioteca, 1002, 50);
    library_lend(biblioteca, 1002, 50);
    library_lend(biblioteca, 1003, 50);
    library_give_back(biblioteca, 1003, 50);
    library_give_back(biblioteca, 1001, 50);

    member_list_print(biblioteca->miembros);

    std::cout << "HISTORIAL:\n";
    stack_print_top(biblioteca->historial, 4);

    library_destroy(biblioteca);
}