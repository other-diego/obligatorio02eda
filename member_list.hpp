#ifndef MEMBER_LIST_HPP
#define MEMBER_LIST_HPP

#include "member.hpp"

struct MemberList;

MemberList *member_list_create();

bool member_list_insert(MemberList *list, Member *m);

Member *member_list_find(const MemberList *list, int num);

bool member_list_remove(MemberList *list, int num);

int member_list_count(const MemberList *list);

void member_list_print(const MemberList *list);

void member_list_destroy(MemberList *list);

#endif