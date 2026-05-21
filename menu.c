#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "books.h"
#include "members.h"
#include "borrowing.h"
#include "filehandling.h"

// Global data arrays (static to this file)
static Book books[MAX_BOOKS];
static int bookCount = 0;

static Member members[MAX_MEMBERS];
static int memberCount = 0;

static Borrowing borrowings[MAX_BORROWINGS];
static int borrowCount = 0;

// Helper to save all data before exit
static void saveAllData(void) {
    saveBooksToFile("books.txt", books, bookCount);
    saveMembersToFile("members.txt", members, memberCount);
    saveBorrowingsToFile("borrowings.txt", borrowings, borrowCount);
}

void runMainMenu(void) {
    // Load existing data
    loadBooksFromFile("books.txt", books, &bookCount);
    loadMembersFromFile("members.txt", members, &memberCount);
    loadBorrowingsFromFile("borrowings.txt", borrowings, &borrowCount);

    int choice;
    do {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Display all books\n");
        printf("2. Search book by title\n");
        printf("3. Search book by author\n");
        printf("4. Add new book\n");
        printf("5. Update book quantity\n");
        printf("6. Remove book\n");
        printf("7. Member Management\n");
        printf("8. Borrowing Management\n");
        printf("9. Generate Inventory Report\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                displayAllBooks(books, bookCount);
                break;
            case 2:
                searchBookByTitle(books, bookCount);
                break;
            case 3:
                searchBookByAuthor(books, bookCount);
                break;
            case 4:
                addBook(books, &bookCount);
                saveBooksToFile("books.txt", books, bookCount);
                break;
            case 5:
                updateBookQuantity(books, bookCount);
                saveBooksToFile("books.txt", books, bookCount);
                break;
            case 6:
                removeBook(books, &bookCount);
                saveBooksToFile("books.txt", books, bookCount);
                break;
            case 7: {
                int mchoice;
                do {
                    printf("\n--- Member Management ---\n");
                    printf("1. Register new member\n");
                    printf("2. View all members\n");
                    printf("3. Update member info\n");
                    printf("0. Back to main menu\n");
                    printf("Choice: ");
                    scanf("%d", &mchoice);
                    while (getchar() != '\n');
                    switch (mchoice) {
                        case 1:
                            registerMember(members, &memberCount);
                            saveMembersToFile("members.txt", members, memberCount);
                            break;
                        case 2:
                            viewAllMembers(members, memberCount);
                            break;
                        case 3:
                            updateMember(members, memberCount);
                            saveMembersToFile("members.txt", members, memberCount);
                            break;
                        case 0: break;
                        default: printf("Invalid choice.\n");
                    }
                } while (mchoice != 0);
                break;
            }
            case 8: {
                int bchoice;
                do {
                    printf("\n--- Borrowing Management ---\n");
                    printf("1. Issue book to member\n");
                    printf("2. Return book\n");
                    printf("3. View borrowing history\n");
                    printf("0. Back to main menu\n");
                    printf("Choice: ");
                    scanf("%d", &bchoice);
                    while (getchar() != '\n');
                    switch (bchoice) {
                        case 1:
                            issueBook(borrowings, &borrowCount, books, bookCount, members, memberCount);
                            saveBooksToFile("books.txt", books, bookCount);
                            saveBorrowingsToFile("borrowings.txt", borrowings, borrowCount);
                            break;
                        case 2:
                            returnBook(borrowings, borrowCount, books, bookCount);
                            saveBooksToFile("books.txt", books, bookCount);
                            saveBorrowingsToFile("borrowings.txt", borrowings, borrowCount);
                            break;
                        case 3:
                            viewBorrowingHistory(borrowings, borrowCount, members, memberCount, books, bookCount);
                            break;
                        case 0: break;
                        default: printf("Invalid choice.\n");
                    }
                } while (bchoice != 0);
                break;
            }
            case 9:
                generateInventoryReport("inventory_report.txt", books, bookCount);
                break;
            case 0:
                printf("Saving data and exiting...\n");
                saveAllData();
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while (choice != 0);
}
