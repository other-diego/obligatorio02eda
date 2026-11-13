
#ifndef STACK_HPP
#define STACK_HPP

#include <string>

struct Stack;

Stack* stack_create();

void stack_push(Stack* s, const std::string& value);

std::string stack_pop(Stack* s);

bool stack_is_empty(const Stack* s);

void stack_print_top(const Stack* s, int n);

void stack_destroy(Stack* s);

#endif
