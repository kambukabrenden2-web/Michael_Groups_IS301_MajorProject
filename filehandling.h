#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "books.h"
#include "members.h"
#include "borrowing.h"

void loadBooksFromFile(const char *filename, Book *books, int *count);
void saveBooksToFile(const char *filename, Book *books, int count);

void loadMembersFromFile(const char *filename, Member *members, int *count);
void saveMembersToFile(const char *filename, Member *members, int count);

void loadBorrowingsFromFile(const char *filename, Borrowing *borrowings, int *count);
void saveBorrowingsToFile(const char *filename, Borrowing *borrowings, int count);

void generateInventoryReport(const char *filename, Book *books, int count);

#endif
