// استعارة، إرجاع، عرض الكتب المتاحة (User Borrowing)
#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#define DATA_FILE "books.txt"

#include "book.h"
#include "user.h"
#include <stdio.h>

void viewAvailableBooks();
void borrowBook();
void returnBook();
void searchByTitle();

#endif
