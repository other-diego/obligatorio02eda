#include <iostream>
#include "member.hpp"
using namespace std;

void test_member() {
    Member *m = member_create(1001, "Bruno");
    cout << member_number(m) << " "; // esperado: 1001
    cout << member_name(m) << " ";   // esperado: Bruno
    cout << member_loans(m) << " ";  // esperado: 0
    cout << member_reservations(m) << " "; // esperado: 0
    cout << member_commitments(m) << endl; // esperado: 0

    member_add_loan(m, 50);
    member_add_loan(m, 20);
    member_add_loan(m, 70);
    cout << member_loans(m) << endl; // esperado: 3

    cout << member_has_loan(m, 50) << " "; // esperado: 1
    cout << member_has_loan(m, 99) << endl; // esperado: 0

    bool removed = member_remove_loan(m, 20);
    cout << removed << " "; // esperado: 1
    cout << member_loans(m) << endl; // esperado: 2

    member_add_reservation(m);
    member_add_reservation(m);
    member_add_loan(m, 5);
    cout << member_commitments(m) << endl; // esperado: 3

    member_destroy(m);
    cout << "test_member OK" << endl;
}
