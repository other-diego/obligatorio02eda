#include <cassert>
#include <iostream>
#include "member.hpp"

int main() {
    Member *m = member_create(1001, "Bruno");
    assert(member_number(m) == 1001);
    assert(member_name(m) == "Bruno");
    assert(member_loans(m) == 0);
    assert(member_reservations(m) == 0);
    assert(member_commitments(m) == 0);

    member_add_loan(m, 50);
    member_add_loan(m, 20);
    member_add_loan(m, 70);
    assert(member_loans(m) == 3);
    assert(member_has_loan(m, 50));
    assert(member_has_loan(m, 20));
    assert(member_has_loan(m, 70));
    assert(!member_has_loan(m, 99));

    assert(member_remove_loan(m, 20));
    assert(member_loans(m) == 2);
    assert(!member_has_loan(m, 20));
    assert(!member_remove_loan(m, 20));

    assert(member_remove_loan(m, 70));
    assert(member_remove_loan(m, 50));
    assert(member_loans(m) == 0);

    member_add_reservation(m);
    member_add_reservation(m);
    assert(member_reservations(m) == 2);
    member_add_loan(m, 5);
    assert(member_commitments(m) == 3);
    member_remove_reservation(m);
    assert(member_reservations(m) == 1);
    assert(member_commitments(m) == 2);

    member_destroy(m);

    std::cout << "test_member OK" << std::endl;
    return 0;
}