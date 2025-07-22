#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "book.h"

void load_books(Book books[], int *count);
void save_books(const Book books[], int count);

#endif
