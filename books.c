#include <stdio.h>
#include <string.h>

#include "books.h"

struct Book books[MAX_BOOKS];
int bookCount = 0;

void addBook()
{
    struct Book b;
    int i;

    if(bookCount >= MAX_BOOKS)
    {
        printf("Book Storage Full!\n");
        return;
    }

    printf("\nEnter Book ID: ");
    scanf("%d", &b.bookID);

    for(i = 0; i < bookCount; i++)
    {
        if(books[i].bookID == b.bookID)
        {
            printf("Book ID Already Exists!\n");
            return;
        }
    }

    getchar();

    printf("Enter Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = 0;

    printf("Enter Author: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    printf("Enter Genre: ");
    fgets(b.genre, sizeof(b.genre), stdin);
    b.genre[strcspn(b.genre, "\n")] = 0;

    printf("Enter Year Published: ");
    scanf("%d", &b.yearPublished);

    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    books[bookCount++] = b;

    printf("Book Added Successfully!\n");
}

void displayAllBooks()
{
    int i;

    if(bookCount == 0)
    {
        printf("No Books Available.\n");
        return;
    }

    printf("\n=========== BOOK LIST ===========\n");

    for(i = 0; i < bookCount; i++)
    {
        printf("Book ID: %d\n", books[i].bookID);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Genre: %s\n", books[i].genre);
        printf("Year Published: %d\n", books[i].yearPublished);
        printf("Quantity: %d\n", books[i].quantity);
        printf("--------------------------------\n");
    }
}

void searchBook()
{
    char keyword[100];
    int i;
    int found = 0;

    getchar();

    printf("Enter Title or Author: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    for(i = 0; i < bookCount; i++)
    {
        if(strstr(books[i].title, keyword) != NULL ||
           strstr(books[i].author, keyword) != NULL)
        {
            printf("\nBook Found!\n");
            printf("Book ID: %d\n", books[i].bookID);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Genre: %s\n", books[i].genre);
            printf("Quantity: %d\n", books[i].quantity);

            found = 1;
        }
    }

    if(!found)
    {
        printf("Book Not Found!\n");
    }
}

void updateQuantity()
{
    int id;
    int qty;
    int i;
    int found = 0;

    printf("Enter Book ID: ");
    scanf("%d", &id);

    for(i = 0; i < bookCount; i++)
    {
        if(books[i].bookID == id)
        {
            printf("Enter New Quantity: ");
            scanf("%d", &qty);

            books[i].quantity = qty;

            found = 1;

            printf("Quantity Updated Successfully!\n");
            break;
        }
    }

    if(!found)
    {
        printf("Book Not Found!\n");
    }
}

void removeBook()
{
    int id;
    int i;
    int j;
    int found = 0;

    printf("Enter Book ID to Remove: ");
    scanf("%d", &id);

    for(i = 0; i < bookCount; i++)
    {
        if(books[i].bookID == id)
        {
            found = 1;

            for(j = i; j < bookCount - 1; j++)
            {
                books[j] = books[j + 1];
            }

            bookCount--;

            printf("Book Removed Successfully!\n");
            break;
        }
    }

    if(!found)
    {
        printf("Book Not Found!\n");
    }
}