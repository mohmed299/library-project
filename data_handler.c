#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_handler.h"

#define DATA_FILE "books.txt"

void load_books(Book books[], int *count) {
    FILE *file = fopen(DATA_FILE, "r");
    if (!file) {
        *count = 0;
        return;
    }

    *count = 0;
    while (fscanf(file, "%d|%[^|]|%[^|]|%d|%d\n",
                  &books[*count].id,
                  books[*count].title,
                  books[*count].author,
                  &books[*count].publication_year,
                  &books[*count].is_borrowed) == 5) {
        (*count)++;
    }

    fclose(file);
}

void save_books(const Book books[], int count) {
    FILE *file = fopen(DATA_FILE, "w");
    if (!file) {
        printf("Error saving books!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s|%d|%d\n",
                books[i].id,
                books[i].title,
                books[i].author,
                books[i].publication_year,
                books[i].is_borrowed);
    }

    fclose(file);
}

void viewAvailableBooks() {
    Book books[MAX_BOOKS];
    int count;
    load_books(books, &count);

    printf("\n--- Available Books ---\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (!books[i].is_borrowed) {
            printf("ID: %d\n", books[i].id);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Year: %d\n", books[i].publication_year);
            printf("--------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No books available at the moment.\n");
    }
}

void borrowBook() {
    int id;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &id);

    Book books[MAX_BOOKS];
    int count;
    load_books(books, &count);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (books[i].id == id && !books[i].is_borrowed) {
            books[i].is_borrowed = 1;
            printf("You have successfully borrowed the book: %s\n", books[i].title);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found or already borrowed.\n");
    } else {
        save_books(books, count);
    }
}

void returnBook() {
    int id;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    Book books[MAX_BOOKS];
    int count;
    load_books(books, &count);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (books[i].id == id && books[i].is_borrowed) {
            books[i].is_borrowed = 0;
            printf("You have successfully returned the book: %s\n", books[i].title);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found or was not borrowed.\n");
    } else {
        save_books(books, count);
    }
}

void searchByTitle() {
    char title[100];
    printf("Enter title to search: ");
    scanf(" %[^\n]", title);  // read full line

    Book books[MAX_BOOKS];
    int count;
    load_books(books, &count);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(books[i].title, title)) {
            printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nStatus: %s\n\n",
                   books[i].id,
                   books[i].title,
                   books[i].author,
                   books[i].publication_year,
                   books[i].is_borrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }

    if (!found) {
        printf("No book found with that title.\n");
    }
}

void filterByAuthor() {
    char author[100];
    printf("Enter author name to filter: ");
    scanf(" %[^\n]", author);  // read full line

    Book books[MAX_BOOKS];
    int count;
    load_books(books, &count);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(books[i].author, author)) {
            printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nStatus: %s\n\n",
                   books[i].id,
                   books[i].title,
                   books[i].author,
                   books[i].publication_year,
                   books[i].is_borrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }

    if (!found) {
        printf("No books found by that author.\n");
    }
}

void filterByYear() {
    int year;
    printf("Enter publication year to filter: ");
    scanf("%d", &year);

    Book books[MAX_BOOKS];
    int count;
    load_books(books, &count);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (books[i].publication_year == year) {
            printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nStatus: %s\n\n",
                   books[i].id,
                   books[i].title,
                   books[i].author,
                   books[i].publication_year,
                   books[i].is_borrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }

    if (!found) {
        printf("No books found from that year.\n");
    }
}
