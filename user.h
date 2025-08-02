#ifndef USER_H
#define USER_H

#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function declarations only (no definitions in header)
void viewAvailableBooks();
void borrowBook();
void returnBook();
void searchByTitle();
void filterByAuthor();
void filterByYear();
void toLowerStr(char *str);
void init_user_pointers();

#endif
