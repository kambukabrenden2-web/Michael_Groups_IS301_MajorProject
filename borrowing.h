#ifndef BORROWING_H
#define BORROWING_H

#include "config.h"
#include "books.h"
#include "members.h"

typedef struct {
    int borrowId;
    int bookId;
    int memberId;
    char borrowDate[DATE_LEN];
    char returnDate[DATE_LEN];
} Borrowing;

void issueBook(Borrowing *borrowings, int *borrowCount,
               Book *books, int bookCount,
               Member *members, int memberCount);
void returnBook(Borrowing *borrowings, int borrowCount,
                Book *books, int bookCount);
void viewBorrowingHistory(Borrowing *borrowings, int borrowCount,
                          Member *members, int memberCount,
                          Book *books, int bookCount);
int findActiveBorrowing(Borrowing *borrowings, int count, int bookId, int memberId);

#endif
