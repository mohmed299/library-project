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
        printf("Library is full! Cannot add more books.\n");
        return;
    }
    
    printf("\n--- Add New Book ---\n");
    printf("Enter book title: ");
    fgets(library[book_count].title, MAX_TITLE_LEN, stdin);
    library[book_count].title[strcspn(library[book_count].title, "\n")] = 0; // Remove newline
    
    printf("Enter author name: ");
    fgets(library[book_count].author, MAX_AUTHOR_LEN, stdin);
    library[book_count].author[strcspn(library[book_count].author, "\n")] = 0; // Remove newline
    
    printf("Enter publication year: ");
    while (scanf("%d", &library[book_count].publication_year) != 1) {
        clear_input_buffer();
        printf("Invalid input! Please enter a valid year: ");
    }
    clear_input_buffer();
    
    library[book_count].id = next_id++;
    library[book_count].is_borrowed = 0;
    
    book_count++;
    printf("Book added successfully! (ID: %d)\n", library[book_count-1].id);
}

// remove books

// Forward declarations for helper functions
void clear_input_buffer();
int find_book_by_id(int id);

void remove_book() {
    if (book_count == 0) {
        printf("No books in the library to remove.\n");
        return;
    }
    
    int id;
    printf("\n--- Remove Book ---\n");
    printf("Enter book ID to remove: ");
    
    if (scanf("%d", &id) != 1) {
        clear_input_buffer();
        printf("Invalid input!\n");
        return;
    }
    clear_input_buffer();
    
    int index = find_book_by_id(id);
    if (index == -1) {
        printf("Book with ID %d not found.\n", id);
        return;
    }
    
    printf("Book found: \"%s\" by %s\n", library[index].title, library[index].author);
    printf("Are you sure you want to remove this book? (y/n): ");

    char confirm;
    if (scanf(" %c", &confirm) != 1 || (confirm != 'y' && confirm != 'n')) {
        clear_input_buffer();
        printf("Invalid input!\n");
        return;
    }
    clear_input_buffer();

    if (confirm == 'y') {
        // Remove the book
        for (int i = index; i < book_count - 1; i++) {
            library[i] = library[i + 1];
        }
        book_count--;
        printf("Book with ID %d removed successfully.\n", id);
    } else {
        printf("Book removal canceled.\n");
    }
}

// count total books

void count_total_books() {
    printf("\n--- Book Statistics ---\n");
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

void view_available_books() {
    int available_count = 0;
    
    printf("\n--- Available Books ---\n");
    printf("%-5s %-30s %-20s %-6s\n", "ID", "Title", "Author", "Year");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < book_count; i++) {
        if (!library[i].is_borrowed) {
            printf("%-5d %-30s %-20s %-6d\n",
                   library[i].id,
                   library[i].title,
                   library[i].author,
                   library[i].publication_year);
            available_count++;
        }
    }
    
    if (available_count == 0) {
        printf("No books are currently available.\n");
    } else {
        printf("\nTotal available books: %d\n", available_count);
    }
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
