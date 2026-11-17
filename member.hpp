#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <string>

struct Member;

Member *member_create(int num, const std::string &name);

int member_number(const Member *m);
std::string member_name(const Member *m);

bool member_has_loan(const Member *m, int code);

void member_add_loan(Member *m, int code);

bool member_remove_loan(Member *m, int code);

int member_loans(const Member *m);

int member_reservations(const Member *m);
void member_add_reservation(Member *m);

void member_remove_reservation(Member *m);

int member_commitments(const Member *m);

void member_destroy(Member *m);

#endif