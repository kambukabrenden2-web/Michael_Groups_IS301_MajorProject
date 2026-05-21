#ifndef BOOKS_H
#define BOOKS_H

#define MAX_BOOKS 100

struct Book
{
    int bookID;
    char title[100];
    char author[100];
    char genre[50];
    int yearPublished;
    int quantity;
};

extern struct Book books[MAX_BOOKS];
extern int bookCount;

void addBook();
void displayAllBooks();
void searchBook();
void updateQuantity();
void removeBook();

#endif