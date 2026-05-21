
#ifndef MEMBERS_H
#define MEMBERS_H

#include "config.h"

typedef struct {
    int id;
    char name[MAX_STRING];
    char email[MAX_STRING];
    char phone[20];
} Member;

void registerMember(Member *members, int *count);
void viewAllMembers(Member *members, int count);
void updateMember(Member *members, int count);
int findMemberIndexById(Member *members, int count, int id);
void displayMember(const Member *m);

#endif