#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "book.h"

void display_book(const Book *book) {
    printf("ID: %d\n", book->id);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("Year: %d\n", book->publication_year);
    printf("Status: %s\n", book->is_borrowed ? "Borrowed" : "Available");
    printf("--------------------\n");
}

int get_next_id(const Book *books, int count) {
    if (count == 0) {
        return 1;
    }
    int max_id = INT_MIN;
    for (int i = 0; i < count; i++) {
        if (books[i].id > max_id) {
            max_id = books[i].id;
        }
    }
    return max_id + 1;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
