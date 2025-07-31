#include <stdio.h>
#include <stdlib.h> // For fopen, fclose, fscanf, fprintf
#include <string.h> // For strcspn

#include "data_handler.h"

// Function to load books from a text file
int load_books(const char *filename, Book *books, int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // If the file doesn't exist, it's normal for the first run
        // or if it's empty. Initialize count to 0.
        *count = 0;
        return 0; // Indicate failure to open/load
    }

    *count = 0; // Reset book count before loading
    // Read 5 fields (ID, Title, Author, Year, is_borrowed)
    while (*count < MAX_BOOKS &&
           fscanf(file, "%d;%99[^;];%99[^;];%d;%d\n",
                  &books[*count].id,
                  books[*count].title,
                  books[*count].author,
                  &books[*count].publication_year, // Corrected member name
                  &books[*count].is_borrowed) == 5) { // Corrected member name
        (*count)++;
    }

    fclose(file);
    return 1; // Indicate successful loading
}

// Function to save books to a text file
int save_books(const char *filename, const Book *books, int current_book_count) { // Parameter renamed to avoid conflict
    FILE *file = fopen(filename, "w"); // Open file for writing (clears old content)
    if (file == NULL) {
        perror("Error opening file for saving"); // Print error message
        return 0; // Indicate save failure
    }

    for (int i = 0; i < current_book_count; i++) {
        fprintf(file, "%d;%s;%s;%d;%d\n",
                books[i].id,
                books[i].title,
                books[i].author,
                books[i].publication_year, // Corrected member name
                books[i].is_borrowed);      // Corrected member name
    }

    fclose(file);
    return 1; // Indicate successful saving
}
