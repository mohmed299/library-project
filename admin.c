// إدارة الكتب: إضافة - حذف - عد (Admin Functions)
#include <stdio.h>

void addBook();
void removeBook();
void countTotalBooks();
    




//view all books and view borrowed books
#include "book.h"
#include "admin.h"

void view_all_books(const Book books[], int count) {
    if (count == 0) {
        printf(" No books in the library.\n");
        return;
    }

    printf(" All Books in the Library:\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nBorrowed: %s\n\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].publication_year,
               books[i].is_borrowed ? "Yes" : "No");
    }
}

void view_borrowed_books(const Book books[], int count) {
    int found = 0;

    printf(" Borrowed Books:\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if (books[i].is_borrowed) {
            found = 1;
            printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\n\n",
                   books[i].id,
                   books[i].title,
                   books[i].author,
                   books[i].publication_year);
        }
    }

    if (!found) {
        printf(" No books are currently borrowed.\n");
    }
}
