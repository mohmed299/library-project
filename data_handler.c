
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_handler.h"

#define DATA_FILE "books.txt"

void load_books(Book books[], int *count) {
    FILE *file = fopen(DATA_FILE, "r");
    if (!file) {
        *count = 0;
        return;
    }

    *count = 0;
    while (fscanf(file, "%d|%[^|]|%[^|]|%d|%d\n",
                  &books[*count].id,
                  books[*count].title,
                  books[*count].author,
                  &books[*count].publication_year,
                  &books[*count].is_borrowed) == 5) {
        (*count)++;
    }

    fclose(file);
}

void save_books(const Book books[], int count) {
    FILE *file = fopen(DATA_FILE, "w");
    if (!file) {
        printf("Error saving books!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s|%d|%d\n",
                books[i].id,
                books[i].title,
                books[i].author,
                books[i].publication_year,
                books[i].is_borrowed);
    }

    fclose(file);
}
