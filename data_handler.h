#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "book.h" // Include header for Book structure

// Function declarations for data handling
// Loads book data from a file into the 'books' array
int load_books(const char *filename, Book *books, int *count);
// Saves book data from the 'books' array to a file
int save_books(const char *filename, const Book *books, int count);

#endif // DATA_HANDLER_H
