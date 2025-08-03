#include <stdio.h>
#include <string.h>
#include <limits.h> // For INT_MIN

#include "book.h"

// Function to display details of a single book
void display_book(const Book *book) {
    printf("ID: %d\n", book->id);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("Year: %d\n", book->publication_year); // Corrected name
    printf("Status: %s\n", book->is_borrowed ? "Borrowed" : "Available"); // Corrected name
    printf("--------------------\n");
}

// Function to get the next available unique ID for a new book
// It finds the maximum existing ID and increments it by 1.
int get_next_id(const Book *books, int count) {
    if (count == 0) {
        return 1; // If no books exist, start with ID 1
    }
    int max_id = INT_MIN; // Initialize with the smallest possible integer value
    for (int i = 0; i < count; i++) {
        if (books[i].id > max_id) {
            max_id = books[i].id;
        }
    }
    return max_id + 1; // The new ID is the max existing ID + 1
}

// Function to clear the standard input buffer
// Used to prevent issues with leftover newline characters after scanf
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
