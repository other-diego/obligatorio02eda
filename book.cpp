
#include "book.hpp"

using namespace std;

struct Book {
    int codigo;
    int ejemplaresTotales;
    int ejemplaresDisponibles;

    string titulo;
    string autor;

    Queue* reservas;
};


Book* book_create(int code, int copies,
                  const string& title,
                  const string& author) {

    Book* nuevo = new Book;

    nuevo->codigo = code;
    nuevo->ejemplaresTotales = copies;
    nuevo->ejemplaresDisponibles = copies;

    nuevo->titulo = title;
    nuevo->autor = author;

    nuevo->reservas = queue_create();

    return nuevo;
}


int book_code(const Book* b) {
    return b->codigo;
}


string book_title(const Book* b) {
    return b->titulo;
}


string book_author(const Book* b) {
    return b->autor;
}


int book_available(const Book* b) {
    return b->ejemplaresDisponibles;
}


int book_total(const Book* b) {
    return b->ejemplaresTotales;
}


Queue* book_reservations(Book* b) {
    return b->reservas;
}


bool book_lend(Book* b) {
    if (b->ejemplaresDisponibles > 0) {
        b->ejemplaresDisponibles--;
        return true;
    }

    return false;
}


void book_give_back(Book* b) {
    b->ejemplaresDisponibles++;
}


void book_destroy(Book* b) {
    queue_destroy(b->reservas);

    delete b;
}
