
#include "members.h"
#include <stdio.h>
#include <string.h>

static int getNextMemberId(Member *members, int count) {
    int maxId = 0;
    for (int i = 0; i < count; i++) {
        if (members[i].id > maxId) maxId = members[i].id;
    }
    return maxId + 1;
}

void registerMember(Member *members, int *count) {
    if (*count >= MAX_MEMBERS) {
        printf("Error: Member limit reached.\n");
        return;
    }
    Member newMember;
    newMember.id = getNextMemberId(members, *count);

    printf("Enter full name: ");
    fgets(newMember.name, MAX_STRING, stdin);
    newMember.name[strcspn(newMember.name, "\n")] = '\0';

    printf("Enter email: ");
    fgets(newMember.email, MAX_STRING, stdin);
    newMember.email[strcspn(newMember.email, "\n")] = '\0';

    printf("Enter phone: ");
    fgets(newMember.phone, 20, stdin);
    newMember.phone[strcspn(newMember.phone, "\n")] = '\0';

    members[*count] = newMember;
    (*count)++;
    printf("Member registered successfully! ID: %d\n", newMember.id);
}

void viewAllMembers(Member *members, int count) {
    if (count == 0) {
        printf("No members registered.\n");
        return;
    }
    printf("\n%-8s %-25s %-30s %-15s\n", "ID", "Name", "Email", "Phone");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-8d %-25s %-30s %-15s\n",
               members[i].id, members[i].name, members[i].email, members[i].phone);
    }
}

void updateMember(Member *members, int count) {
    int id;
    printf("Enter Member ID to update: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    int idx = findMemberIndexById(members, count, id);
    if (idx == -1) {
        printf("Member ID %d not found.\n", id);
        return;
    }
    printf("Updating member: %s\n", members[idx].name);
    printf("New name (enter to keep current): ");
    char newName[MAX_STRING];
    fgets(newName, MAX_STRING, stdin);
    newName[strcspn(newName, "\n")] = '\0';
    if (strlen(newName) > 0) strcpy(members[idx].name, newName);

    printf("New email (enter to keep): ");
    char newEmail[MAX_STRING];
    fgets(newEmail, MAX_STRING, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';
    if (strlen(newEmail) > 0) strcpy(members[idx].email, newEmail);

    printf("New phone (enter to keep): ");
    char newPhone[20];
    fgets(newPhone, 20, stdin);
    newPhone[strcspn(newPhone, "\n")] = '\0';
    if (strlen(newPhone) > 0) strcpy(members[idx].phone, newPhone);

    printf("Member information updated.\n");
}

int findMemberIndexById(Member *members, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (members[i].id == id) return i;
    }
    return -1;
}

void displayMember(const Member *m) {
    printf("ID: %d | Name: %s | Email: %s | Phone: %s\n",
           m->id, m->name, m->email, m->phone);
}
