#include "library.hpp"

void test_library() {
    Library* biblioteca = library_create();

    library_add_book(biblioteca, 50, 1, "Ficciones", "Borges");

    library_add_member(biblioteca, 1001, "Bruno");
    library_add_member(biblioteca, 1002, "Ana");
    library_add_member(biblioteca, 1003, "Eva");

    library_lend(biblioteca, 1001, 50);
    library_lend(biblioteca, 1002, 50);
    library_lend(biblioteca, 1002, 50);
    library_lend(biblioteca, 1003, 50);
    library_give_back(biblioteca, 1003, 50);
    library_give_back(biblioteca, 1001, 50);

    library_print_members(biblioteca);
    library_print_history(biblioteca, 4);
    library_print_stats(biblioteca);

    library_destroy(biblioteca);
}
