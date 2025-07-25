#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

#define LINE_LENGTH 300

void display_book(const Book *book) {
    printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nStatus: %s\n\n",
           book->id, book->title, book->author,
           book->publication_year,
           book->is_borrowed ? "Borrowed" : "Available");
}

int load_books_from_file(const char *filename, Book *books, int max_books) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    int count = 0;
    char line[LINE_LENGTH];
    while (count < max_books && fgets(line, sizeof(line), file)) {
        Book b;
        char *token = strtok(line, "|");
        if (token) b.id = atoi(token);

        token = strtok(NULL, "|");
        if (token) strcpy(b.title, token);

        token = strtok(NULL, "|");
        if (token) strcpy(b.author, token);

        token = strtok(NULL, "|");
        if (token) b.publication_year = atoi(token);

        token = strtok(NULL, "|\n");
        if (token) b.is_borrowed = atoi(token);

        books[count++] = b;
    }

    fclose(file);
    return count;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
