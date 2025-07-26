// عرض كل الكتب والكتب المستعارة (Admin View)
#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include "book.h"

// fynction to find book by ID
int find_book_by_id(const Book *books, int count, int id);

// Admin Function 2: View all books and borrowed books
void view_all_books(const Book books[], int count);
void view_borrowed_books(const Book books[], int count);


#endif

