#include "member_list.hpp"
#include <iostream>

using namespace std;

struct MemberListNode {
    Member *member;
    MemberListNode *next;
};

struct MemberList {
    MemberListNode *head;
    int count;
};

// Funciones recursivas auxiliares (ya sin static)
Member *member_list_find_rec(MemberListNode *node, int num) {
    if (node == nullptr) return nullptr;
    int n = member_number(node->member);
    if (num == n) return node->member;
    if (num < n) return nullptr;
    return member_list_find_rec(node->next, num);
}

void member_list_destroy_rec(MemberListNode *node) {
    if (node == nullptr) return;
    member_list_destroy_rec(node->next);
    member_destroy(node->member);
    delete node;
}

MemberList *member_list_create() {
    MemberList *list = new MemberList;
    list->head = nullptr;
    list->count = 0;
    return list;
}

bool member_list_insert(MemberList *list, Member *m) {
    if (list == nullptr || m == nullptr) return false;

    int num = member_number(m);
    if (member_list_find(list, num) != nullptr) return false;

    MemberListNode *node = new MemberListNode;
    node->member = m;
    node->next = nullptr;

    if (list->head == nullptr || num < member_number(list->head->member)) {
        node->next = list->head;
        list->head = node;
    } else {
        MemberListNode *prev = list->head;
        while (prev->next != nullptr && member_number(prev->next->member) < num) {
            prev = prev->next;
        }
        node->next = prev->next;
        prev->next = node;
    }

    list->count++;
    return true;
}

Member *member_list_find(const MemberList *list, int num) {
    if (list == nullptr) return nullptr;
    return member_list_find_rec(list->head, num);
}

bool member_list_remove(MemberList *list, int num) {
    if (list == nullptr || list->head == nullptr) return false;

    MemberListNode *to_delete = nullptr;

    if (member_number(list->head->member) == num) {
        to_delete = list->head;
        list->head = list->head->next;
    } else {
        MemberListNode *prev = list->head;
        while (prev->next != nullptr && member_number(prev->next->member) != num) {
            prev = prev->next;
        }
        if (prev->next == nullptr) return false;
        to_delete = prev->next;
        prev->next = to_delete->next;
    }

    member_destroy(to_delete->member);
    delete to_delete;
    list->count--;
    return true;
}

int member_list_count(const MemberList *list) {
    return list == nullptr ? 0 : list->count;
}

void member_list_print(const MemberList *list) {
    cout << "SOCIOS:" << endl;
    if (list == nullptr) return;

    for (MemberListNode *node = list->head; node != nullptr; node = node->next) {
        Member *m = node->member;
        cout << member_number(m) << " " << member_name(m)
             << " prestamos=" << member_loans(m)
             << " reservas=" << member_reservations(m) << endl;
    }
}

void member_list_destroy(MemberList *list) {
    if (list == nullptr) return;
    member_list_destroy_rec(list->head);
    delete list;
}