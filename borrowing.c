#include "borrowing.h"
#include <stdio.h>
#include <string.h>

static int getNextBorrowId(Borrowing *borrowings, int count) {
    int maxId = 0;
    for (int i = 0; i < count; i++) {
        if (borrowings[i].borrowId > maxId) maxId = borrowings[i].borrowId;
    }
    return maxId + 1;
}

void issueBook(Borrowing *borrowings, int *borrowCount,
               Book *books, int bookCount,
               Member *members, int memberCount) {
    int bookId, memberId;
    printf("Enter Book ID: ");
    scanf("%d", &bookId);
    printf("Enter Member ID: ");
    scanf("%d", &memberId);
    while (getchar() != '\n');

    int bookIdx = findBookIndexById(books, bookCount, bookId);
    if (bookIdx == -1) {
        printf("Book ID %d not found.\n", bookId);
        return;
    }
    if (books[bookIdx].quantity <= 0) {
        printf("Book '%s' is currently not available.\n", books[bookIdx].title);
        return;
    }
    int memberIdx = findMemberIndexById(members, memberCount, memberId);
    if (memberIdx == -1) {
        printf("Member ID %d not found.\n", memberId);
        return;
    }

    for (int i = 0; i < *borrowCount; i++) {
        if (borrowings[i].bookId == bookId && borrowings[i].memberId == memberId &&
            borrowings[i].returnDate[0] == '\0') {
            printf("This member already has this book borrowed and not yet returned.\n");
            return;
        }
    }

    if (*borrowCount >= MAX_BORROWINGS) {
        printf("Borrowing limit reached.\n");
        return;
    }

    Borrowing newBorrow;
    newBorrow.borrowId = getNextBorrowId(borrowings, *borrowCount);
    newBorrow.bookId = bookId;
    newBorrow.memberId = memberId;
    printf("Enter borrow date (YYYY-MM-DD): ");
    fgets(newBorrow.borrowDate, DATE_LEN, stdin);
    newBorrow.borrowDate[strcspn(newBorrow.borrowDate, "\n")] = '\0';
    newBorrow.returnDate[0] = '\0';

    borrowings[*borrowCount] = newBorrow;
    (*borrowCount)++;

    books[bookIdx].quantity--;
    printf("Book issued successfully. Borrow ID: %d\n", newBorrow.borrowId);
}

void returnBook(Borrowing *borrowings, int borrowCount,
                Book *books, int bookCount) {
    int bookId, memberId;
    printf("Enter Book ID: ");
    scanf("%d", &bookId);
    printf("Enter Member ID: ");
    scanf("%d", &memberId);
    while (getchar() != '\n');

    int borrowIdx = -1;
    for (int i = 0; i < borrowCount; i++) {
        if (borrowings[i].bookId == bookId && borrowings[i].memberId == memberId &&
            borrowings[i].returnDate[0] == '\0') {
            borrowIdx = i;
            break;
        }
    }
    if (borrowIdx == -1) {
        printf("No active borrowing record found for this book and member.\n");
        return;
    }

    printf("Enter return date (YYYY-MM-DD): ");
    char retDate[DATE_LEN];
    fgets(retDate, DATE_LEN, stdin);
    retDate[strcspn(retDate, "\n")] = '\0';
    strcpy(borrowings[borrowIdx].returnDate, retDate);

    int bookIdx = findBookIndexById(books, bookCount, bookId);
    if (bookIdx != -1) {
        books[bookIdx].quantity++;
    }
    printf("Book returned successfully.\n");
}

void viewBorrowingHistory(Borrowing *borrowings, int borrowCount,
                          Member *members, int memberCount,
                          Book *books, int bookCount) {
    if (borrowCount == 0) {
        printf("No borrowing records.\n");
        return;
    }
    printf("\n%-8s %-8s %-8s %-12s %-12s\n", "BorrowID", "BookID", "MemberID", "BorrowDate", "ReturnDate");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < borrowCount; i++) {
        printf("%-8d %-8d %-8d %-12s %-12s\n",
               borrowings[i].borrowId, borrowings[i].bookId, borrowings[i].memberId,
               borrowings[i].borrowDate,
               (borrowings[i].returnDate[0] == '\0') ? "Not yet" : borrowings[i].returnDate);
    }
}

int findActiveBorrowing(Borrowing *borrowings, int count, int bookId, int memberId) {
    for (int i = 0; i < count; i++) {
        if (borrowings[i].bookId == bookId && borrowings[i].memberId == memberId &&
            borrowings[i].returnDate[0] == '\0')
            return i;
    }
    return -1;
}
