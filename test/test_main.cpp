// Corre las pruebas de todos los TAD en un solo ejecutable.
// Cada test_<modulo>.cpp define una funcion test_<modulo>() sin main.
//
// Compilar y correr desde la raiz del repo (todos los .cpp menos main.cpp):
//   g++ -std=c++17 -Wall -Wextra -I. -o test/tests test/*.cpp book.cpp catalog.cpp library.cpp member.cpp member_list.cpp queue.cpp stack.cpp
//   ./test/tests

#include <iostream>
#include <string>

using namespace std;

void test_queue();
void test_stack();
void test_book();
void test_catalog();
void test_member();
void test_member_list();
void test_library();

void correr(const string &nombre, void (*prueba)()) {
    cout << "===== " << nombre << " =====" << endl;
    prueba();
    cout << endl;
}

int main() {
    correr("queue", test_queue);
    correr("stack", test_stack);
    correr("book", test_book);
    correr("catalog", test_catalog);
    correr("member", test_member);
    correr("member_list", test_member_list);
    correr("library", test_library);
    return 0;
}
