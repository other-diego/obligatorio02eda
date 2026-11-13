
#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include "queue.hpp"

struct Book;


Book* book_create(int code, int copies,
                  const std::string& title,
                  const std::string& author);

int book_code(const Book* b);

std::string book_title(const Book* b);

std::string book_author(const Book* b);

int book_available(const Book* b);

int book_total(const Book* b);

Queue* book_reservations(Book* b);

bool book_lend(Book* b);

void book_give_back(Book* b);

void book_destroy(Book* b);

#endif
