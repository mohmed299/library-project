#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "book.h"
#include "admin.h"

Book library[MAX_BOOKS];
int book_count = 0;
int next_id = 1;

// Functions to get addresses of global variables
Book* get_library_address() {
    return library;
}

int* get_book_count_address() {
    return &book_count;
}

int* get_next_id_address() {
    return &next_id;
}

// Function to find book by ID (without pointers)
int find_book_by_id(int id) {
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            return i;
        }
    }
    return -1; // Not found
}

// Function to add a book
void addBook() {
    if (book_count >= MAX_BOOKS) {
        printf("Library is full and you Cannot add more books.\n");
        return;
    }
    
    printf("\n Add New Book \n");
    
    clear_input_buffer(); // Clear any leftover input
    
    printf("Enter the book title: ");
    fgets(library[book_count].title, MAX_TITLE_LEN, stdin);
    library[book_count].title[strcspn(library[book_count].title, "\n")] = 0;
    
    printf("Enter author name: ");
    fgets(library[book_count].author, MAX_AUTHOR_LEN, stdin);
    library[book_count].author[strcspn(library[book_count].author, "\n")] = 0;
    
    printf("Enter publication year: ");
    scanf("%d", &library[book_count].publication_year);
    
    library[book_count].id = next_id++;
    library[book_count].is_borrowed = 0;
    
    book_count++;

    printf("Book added successfully! (ID: %d)\n", library[book_count-1].id);
}

// Function to remove books
void removeBook() {
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

    if (confirm == 'y' || confirm == 'Y') {
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
void countTotalBooks() {
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

    printf("Available books: %d\n", available);
    printf("Borrowed books: %d\n", borrowed);
}

// View all books
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

// View borrowed books
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