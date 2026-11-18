#include <iostream>
#include "member_list.hpp"
using namespace std;

void test_member_list() {
    MemberList *list = member_list_create();
    cout << member_list_count(list) << endl; // esperado: 0

    bool ins1 = member_list_insert(list, member_create(1002, "Ana"));
    bool ins2 = member_list_insert(list, member_create(1001, "Bruno"));
    bool ins3 = member_list_insert(list, member_create(1003, "Carla"));
    cout << ins1 << ins2 << ins3 << endl; // esperado: 111
    cout << member_list_count(list) << endl; // esperado: 3

    Member *m = member_list_find(list, 1001);
    cout << member_name(m) << endl; // esperado: Bruno

    member_add_loan(member_list_find(list, 1002), 50);
    member_add_reservation(member_list_find(list, 1002));

    member_list_print(list);
    // esperado:
    // SOCIOS:
    // 1001 Bruno prestamos=0 reservas=0
    // 1002 Ana prestamos=1 reservas=1
    // 1003 Carla prestamos=0 reservas=0

    bool rem = member_list_remove(list, 1002);
    cout << rem << " "; // esperado: 1
    cout << member_list_count(list) << endl; // esperado: 2

    member_list_destroy(list);
    cout << "test_member_list OK" << endl;
}
