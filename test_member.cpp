#include <iostream>
#include "member.hpp"

int main() {
    Member *m = member_create(1001, "Bruno");
    std::cout << member_number(m) << " "; // esperado: 1001
    std::cout << member_name(m) << " ";   // esperado: Bruno
    std::cout << member_loans(m) << " ";  // esperado: 0
    std::cout << member_reservations(m) << " "; // esperado: 0
    std::cout << member_commitments(m) << std::endl; // esperado: 0

    member_add_loan(m, 50);
    member_add_loan(m, 20);
    member_add_loan(m, 70);
    std::cout << member_loans(m) << std::endl; // esperado: 3

    std::cout << member_has_loan(m, 50) << " "; // esperado: 1
    std::cout << member_has_loan(m, 99) << std::endl; // esperado: 0

    bool removed = member_remove_loan(m, 20);
    std::cout << removed << " "; // esperado: 1
    std::cout << member_loans(m) << std::endl; // esperado: 2

    member_add_reservation(m);
    member_add_reservation(m);
    member_add_loan(m, 5);
    std::cout << member_commitments(m) << std::endl; // esperado: 3

    member_destroy(m);
    std::cout << "test_member OK" << std::endl;
    return 0;
}