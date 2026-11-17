#include "member.hpp"

using namespace std;

struct LoanNode {
    int code;
    LoanNode *next;
};

struct Member {
    int num;
    string name;
    LoanNode *loans;
    int reservations;
};

// Funciones recursivas auxiliares (ya sin static)
int count_loans_rec(LoanNode *node) {
    if (node == nullptr) return 0;
    return 1 + count_loans_rec(node->next);
}

bool remove_loan_rec(LoanNode *&node, int code) {
    if (node == nullptr) return false;
    if (node->code == code) {
        LoanNode *temp = node;
        node = node->next;
        delete temp;
        return true;
    }
    return remove_loan_rec(node->next, code);
}

void destroy_loans_rec(LoanNode *&node) {
    if (node == nullptr) return;
    destroy_loans_rec(node->next);
    delete node;
    node = nullptr;
}

Member *member_create(int num, const string &name) {
    Member *m = new Member;
    m->num = num;
    m->name = name;
    m->loans = nullptr;
    m->reservations = 0;
    return m;
}

int member_number(const Member *m) {
    return m->num;
}

string member_name(const Member *m) {
    return m->name;
}

bool member_has_loan(const Member *m, int code) {
    LoanNode *curr = m->loans;
    while (curr != nullptr) {
        if (curr->code == code) return true;
        curr = curr->next;
    }
    return false;
}

void member_add_loan(Member *m, int code) {
    LoanNode *new_node = new LoanNode;
    new_node->code = code;
    new_node->next = m->loans;
    m->loans = new_node;
}

bool member_remove_loan(Member *m, int code) {
    return remove_loan_rec(m->loans, code);
}

int member_loans(const Member *m) {
    return count_loans_rec(m->loans);
}

int member_reservations(const Member *m) {
    return m->reservations;
}

void member_add_reservation(Member *m) {
    m->reservations++;
}

void member_remove_reservation(Member *m) {
    if (m->reservations > 0) {
        m->reservations--;
    }
}

int member_commitments(const Member *m) {
    return member_loans(m) + member_reservations(m);
}

void member_destroy(Member *m) {
    if (m == nullptr) return;
    destroy_loans_rec(m->loans);
    delete m;
}