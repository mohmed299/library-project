#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include "book.h"

// Function declarations only
int find_book_by_id(int id);
void addBook();
void removeBook();
void countTotalBooks();
void admin_mode();
void view_all_books(const Book books[], int count);
void view_borrowed_books(const Book books[], int count);
void invalid_choice();

// Function to get library array address
Book* get_library_address();
int* get_book_count_address();
int* get_next_id_address();

#endif