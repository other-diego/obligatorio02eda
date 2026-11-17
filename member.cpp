#include "member.hpp"

struct LoanNode {
    int code;
    LoanNode *next;
};

struct Member {
    int num;
    std::string name;
    LoanNode *loans;
    int reservations;
};

static int loans_count(const LoanNode *n) {
    if (n == nullptr) return 0;
    return 1 + loans_count(n->next);
}

static bool loans_contains(const LoanNode *n, int code) {
    if (n == nullptr) return false;
    if (n->code == code) return true;
    return loans_contains(n->next, code);
}

static bool loans_remove(LoanNode *&n, int code) {
    if (n == nullptr) return false;
    if (n->code == code) {
        LoanNode *to_delete = n;
        n = n->next;
        delete to_delete;
        return true;
    }
    return loans_remove(n->next, code);
}

static void loans_destroy(LoanNode *&n) {
    if (n == nullptr) return;
    loans_destroy(n->next);
    delete n;
    n = nullptr;
}

Member *member_create(int num, const std::string &name) {
    Member *m = new Member;
    m->num = num;
    m->name = name;
    m->loans = nullptr;
    m->reservations = 0;
    return m;
}

int member_number(const Member *m) { return m->num; }
std::string member_name(const Member *m) { return m->name; }

bool member_has_loan(const Member *m, int code) {
    return loans_contains(m->loans, code);
}

void member_add_loan(Member *m, int code) {
    LoanNode *node = new LoanNode;
    node->code = code;
    node->next = m->loans;
    m->loans = node;
}

bool member_remove_loan(Member *m, int code) {
    return loans_remove(m->loans, code);
}

int member_loans(const Member *m) { return loans_count(m->loans); }

int member_reservations(const Member *m) { return m->reservations; }
void member_add_reservation(Member *m) { m->reservations++; }
void member_remove_reservation(Member *m) { m->reservations--; }

int member_commitments(const Member *m) {
    return member_loans(m) + member_reservations(m);
}

void member_destroy(Member *m) {
    loans_destroy(m->loans);
    delete m;
}