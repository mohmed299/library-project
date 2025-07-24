// إدارة الكتب: إضافة - حذف - عد (Admin Functions)
#include <stdio.h>
#include "book.h"

void addBook();
void removeBook();
void countTotalBooks();


Book library[MAX_BOOKS];

int book_count = 0;

int next_id = 1;

// Function to add a book
void add_book() {

    if (book_count >= MAX_BOOKS) {

        printf("Library is full and you Cannot add more books.\n");

        return;
    }
    
    printf("\n Add New Book \n");


    printf("Enter the book title: ");


    scanf("%s", library[book_count].title);
    
    printf("Enter author name: ");
    scanf("%s", library[book_count].author);
    
    printf("Enter publication year: ");
    scanf("%d", &library[book_count].publication_year);
    
    library[book_count].id = next_id++;

    library[book_count].is_borrowed = 0;
    
    book_count++;

    printf("Book added successfully! (ID: %d)\n", library[book_count-1].id);
}

// Function to remove books
void remove_book() {
    if (book_count == 0) {


        printf("No books in this library to remove.\n");
        return;
    }
    
    int id;


    printf("\n Remove Book\n");
    printf("Enter book ID to remove: ");
    scanf("%d", &id);
    
    int index = find_book_by_id(id);
    if (index == -1) {
        printf("Book with ID %d not found.\n", id);
        return;
    }
    
    printf("Book was found: \"%s\" by %s\n", library[index].title, library[index].author);

    printf("Are you sure you wanna remove this book? (y/n): ");

    char confirm;
    scanf(" %c", &confirm);

    if (confirm == 'y') {
        for (int i = index; i < book_count - 1; i++) {
            library[i] = library[i + 1];
        }
        book_count--;
        printf("Book with ID %d removed successfully.\n", id);
    } else {
        printf("Book removal canceled.\n");
    }
}


// Function to count total books
void count_total_books() {

    printf("\n Book Count \n");

    printf("Total books in library: %d\n", book_count);
    
    int available = 0, borrowed = 0;

    for (int i = 0; i < book_count; i++) {
        if (library[i].is_borrowed) {
            borrowed++;
        } else {
            available++;
        }
    }  

    printf("Total books: %d\n", book_count);   
}

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
