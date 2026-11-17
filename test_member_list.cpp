#include <iostream>
#include "member_list.hpp"

int main() {
    MemberList *list = member_list_create();
    std::cout << member_list_count(list) << std::endl; // esperado: 0

    bool ins1 = member_list_insert(list, member_create(1002, "Ana"));
    bool ins2 = member_list_insert(list, member_create(1001, "Bruno"));
    bool ins3 = member_list_insert(list, member_create(1003, "Carla"));
    std::cout << ins1 << ins2 << ins3 << std::endl; // esperado: 111
    std::cout << member_list_count(list) << std::endl; // esperado: 3

    Member *m = member_list_find(list, 1001);
    std::cout << member_name(m) << std::endl; // esperado: Bruno

    member_add_loan(member_list_find(list, 1002), 50);
    member_add_reservation(member_list_find(list, 1002));

    member_list_print(list);
    // esperado:
    // SOCIOS:
    // 1001 Bruno prestamos=0 reservas=0
    // 1002 Ana prestamos=1 reservas=1
    // 1003 Carla prestamos=0 reservas=0

    bool rem = member_list_remove(list, 1002);
    std::cout << rem << " "; // esperado: 1
    std::cout << member_list_count(list) << std::endl; // esperado: 2

    member_list_destroy(list);
    std::cout << "test_member_list OK" << std::endl;
    return 0;
}