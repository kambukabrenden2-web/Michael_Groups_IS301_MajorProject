
#include "auth.h"
#include <stdio.h>
#include <string.h>

#define ADMIN_USER "admin"
#define ADMIN_PASS "admin"

bool login(void) {
    char username[50];
    char password[50];

    printf("\n======= LIBRARY MANAGEMENT SYSTEM =======\n");
    printf("Administrator Login\n");
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, ADMIN_USER) == 0 && strcmp(password, ADMIN_PASS) == 0) {
        printf("\nLogin successful!\n");
        return true;
    } else {
        printf("\nInvalid credentials. Access denied.\n");
        return false;
    }
}