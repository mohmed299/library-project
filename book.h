#ifndef BOOK_H
#define BOOK_H


#define MAX_TITLE_LEN 200
#define MAX_AUTHOR_LEN 200
#define MAX_BOOKS 800

// Define the Book structure
typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    int publication_year;
    int is_borrowed;
} Book;

void display_book(const Book *book);
int get_next_id(const Book *books, int count);
void clear_input_buffer();

#endif // BOOK_H
