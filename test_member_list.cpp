#include <cassert>
#include <iostream>
#include "member_list.hpp"

int main() {
    MemberList *list = member_list_create();
    assert(member_list_count(list) == 0);
    assert(member_list_find(list, 1001) == nullptr);

    assert(member_list_insert(list, member_create(1002, "Ana")));
    assert(member_list_insert(list, member_create(1001, "Bruno")));
    assert(member_list_insert(list, member_create(1003, "Carla")));
    assert(member_list_count(list) == 3);

    assert(!member_list_insert(list, member_create(1002, "Duplicado")));

    Member *m = member_list_find(list, 1001);
    assert(m != nullptr);
    assert(member_name(m) == "Bruno");

    member_add_loan(member_list_find(list, 1002), 50);
    member_add_reservation(member_list_find(list, 1002));

    member_list_print(list);

    assert(member_list_remove(list, 1002));
    assert(member_list_count(list) == 2);
    assert(member_list_find(list, 1002) == nullptr);
    assert(!member_list_remove(list, 1002));

    member_list_destroy(list);
    std::cout << "test_member_list OK" << std::endl;
    return 0;
}
