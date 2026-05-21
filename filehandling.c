#include "filehandling.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void loadBooksFromFile(const char *filename, Book *books, int *count) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Warning: %s not found. Starting with empty book list.\n", filename);
        *count = 0;
        return;
    }
    *count = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp) && *count < MAX_BOOKS) {
        Book b;
        if (sscanf(line, "%d,%99[^,],%99[^,],%49[^,],%d,%d",
                   &b.id, b.title, b.author, b.genre, &b.year, &b.quantity) == 6) {
            books[*count] = b;
            (*count)++;
        }
    }
    fclose(fp);
}

void saveBooksToFile(const char *filename, Book *books, int count) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Cannot open %s for writing.\n", filename);
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%s,%d,%d\n",
                books[i].id, books[i].title, books[i].author,
                books[i].genre, books[i].year, books[i].quantity);
    }
    fclose(fp);
}

void loadMembersFromFile(const char *filename, Member *members, int *count) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Warning: %s not found. Starting with empty member list.\n", filename);
        *count = 0;
        return;
    }
    *count = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp) && *count < MAX_MEMBERS) {
        Member m;
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^\n]",
                   &m.id, m.name, m.email, m.phone) == 4) {
            members[*count] = m;
            (*count)++;
        }
    }
    fclose(fp);
}

void saveMembersToFile(const char *filename, Member *members, int count) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Cannot open %s for writing.\n", filename);
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%s\n", members[i].id, members[i].name, members[i].email, members[i].phone);
    }
    fclose(fp);
}

void loadBorrowingsFromFile(const char *filename, Borrowing *borrowings, int *count) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Warning: %s not found. Starting with empty borrowing records.\n", filename);
        *count = 0;
        return;
    }
    *count = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp) && *count < MAX_BORROWINGS) {
        Borrowing b;
        char retDate[DATE_LEN];
        if (sscanf(line, "%d,%d,%d,%10[^,],%10s",
                   &b.borrowId, &b.bookId, &b.memberId, b.borrowDate, retDate) == 5) {
            strcpy(b.returnDate, retDate);
            borrowings[*count] = b;
            (*count)++;
        }
    }
    fclose(fp);
}

void saveBorrowingsToFile(const char *filename, Borrowing *borrowings, int count) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Cannot open %s for writing.\n", filename);
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%d,%d,%s,%s\n",
                borrowings[i].borrowId, borrowings[i].bookId, borrowings[i].memberId,
                borrowings[i].borrowDate,
                (borrowings[i].returnDate[0] == '\0') ? "NULL" : borrowings[i].returnDate);
    }
    fclose(fp);
}

void generateInventoryReport(const char *filename, Book *books, int count) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not create inventory report.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "BookID: %d\n", books[i].id);
        fprintf(fp, "Title: %s\n", books[i].title);
        fprintf(fp, "Author: %s\n", books[i].author);
        fprintf(fp, "Genre: %s\n", books[i].genre);
        fprintf(fp, "Year Published: %d\n", books[i].year);
        fprintf(fp, "Quantity: %d\n", books[i].quantity);
        fprintf(fp, "Availability Status: %s\n", (books[i].quantity > 0) ? "Available" : "Out of Stock");
        fprintf(fp, "----------------------------\n");
    }
    fclose(fp);
    printf("Inventory report saved to %s\n", filename);
}
