#include "user.h"
#include <string.h>   // For: strcspn, strncpy, strstr
#include <ctype.h>    // For: tolower
#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#include "admin.h"

#define MAX_RESULTS 100

// Get pointers to admin data
static Book *library_ptr = NULL;
static int *book_count_ptr = NULL;
static int *next_id_ptr = NULL;

Book searchResults[MAX_RESULTS];
int searchResultCount = 0;

// Initialize pointers to admin data
void init_user_pointers() {
    library_ptr = get_library_address();
    book_count_ptr = get_book_count_address();
    next_id_ptr = get_next_id_address();
}

void toLowerStr(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

//**************************Search By Title******************************//

void searchByTitle() {
    // Initialize pointers if not done already
    if (library_ptr == NULL) {
        init_user_pointers();
    }
    
    char search_title[100];
    printf("Enter the book title to search: ");
    clear_input_buffer();
    fgets(search_title, sizeof(search_title), stdin);
    search_title[strcspn(search_title, "\n")] = 0;

    int found = 0;
    searchResultCount = 0;

    char lower_search_title[100];
    strncpy(lower_search_title, search_title, sizeof(lower_search_title));
    lower_search_title[sizeof(lower_search_title) - 1] = '\0';
    toLowerStr(lower_search_title);

    printf("\nSearching through %d books...\n", *book_count_ptr);

    for (int i = 0; i < *book_count_ptr; i++) {
        char lower_title[100];
        strncpy(lower_title, library_ptr[i].title, sizeof(lower_title));
        lower_title[sizeof(lower_title) - 1] = '\0';
        toLowerStr(lower_title);

        if (strstr(lower_title, lower_search_title)) {
            searchResults[searchResultCount++] = library_ptr[i];
            printf("\nID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nStatus: %s\n",
                   library_ptr[i].id, library_ptr[i].title, library_ptr[i].author,
                   library_ptr[i].publication_year,
                   library_ptr[i].is_borrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }

    if (!found) {
        printf("No books found with title containing \"%s\".\n", search_title);
        return;
    }

    // Offer filter options
    int choice;
    printf("\nFilter search results:\n1. By Author\n2. By Year\n3. Exit\nChoice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: filterByAuthor(); break;
        case 2: filterByYear(); break;
        case 3: default: break;
    }
}

//**************************filter By Author******************************//

void filterByAuthor() {
    char author[100];
    printf("Enter author's name to filter: ");
    clear_input_buffer();
    fgets(author, sizeof(author), stdin);
    author[strcspn(author, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < searchResultCount; i++) {
        if (strstr(searchResults[i].author, author)) {
            printf("\nID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nStatus: %s\n",
                   searchResults[i].id,
                   searchResults[i].title,
                   searchResults[i].author,
                   searchResults[i].publication_year,
                   searchResults[i].is_borrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }

    if (!found) {
        printf("No books found by that author in the search results.\n");
    }
}

//**************************filter By Year******************************//

void filterByYear() {
    int year;
    printf("Enter publication year to filter: ");
    scanf("%d", &year);

    int found = 0;
    for (int i = 0; i < searchResultCount; i++) {
        if (searchResults[i].publication_year == year) {
            printf("\nID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nStatus: %s\n",
                   searchResults[i].id,
                   searchResults[i].title,
                   searchResults[i].author,
                   searchResults[i].publication_year,
                   searchResults[i].is_borrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }

    if (!found) {
        printf("No books found from that year in the search results.\n");
    }
}

//**************************User Borrowing Functions ******************************//

// عرض جميع الكتب المتاحة (التي لم يتم استعارتها)
void viewAvailableBooks() {
    // Initialize pointers if not done already
    if (library_ptr == NULL) {
        init_user_pointers();
    }

    if (*book_count_ptr == 0) {
        printf("No books found, currently.\n");
        return;
    }

    printf("\nAvailable book list:\n");
    printf("--------------------------------------------------\n");
    
    int available_count = 0;
    for (int i = 0; i < *book_count_ptr; i++) {
        if (!library_ptr[i].is_borrowed) {
            printf("ID: %d | %s by %s (%d)\n", 
                   library_ptr[i].id, 
                   library_ptr[i].title, 
                   library_ptr[i].author, 
                   library_ptr[i].publication_year);
            available_count++;
        }
    }
    
    if (available_count == 0) {
        printf("No books are currently available for borrowing.\n");
    }
}

void borrowBook() {
    // Initialize pointers if not done already
    if (library_ptr == NULL) {
        init_user_pointers();
    }

    int id, found = 0;

    if (*book_count_ptr == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("Enter the book ID you desire to borrow: ");
    scanf("%d", &id);

    for (int i = 0; i < *book_count_ptr; i++) {
        if (library_ptr[i].id == id && !library_ptr[i].is_borrowed) {
            library_ptr[i].is_borrowed = 1;
            found = 1;
            printf("The book \"%s\" by %s is borrowed successfully.\n", 
                   library_ptr[i].title, library_ptr[i].author);
            break;
        } else if (library_ptr[i].id == id && library_ptr[i].is_borrowed) {
            printf("The book \"%s\" is already borrowed.\n", library_ptr[i].title);
            return;
        }
    }

    if (!found) {
        printf("The book with ID %d is not found.\n", id);
    }
}

void returnBook() {
    // Initialize pointers if not done already
    if (library_ptr == NULL) {
        init_user_pointers();
    }

    int id, found = 0;

    if (*book_count_ptr == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("Enter the book ID you want to return: ");
    scanf("%d", &id);

    for (int i = 0; i < *book_count_ptr; i++) {
        if (library_ptr[i].id == id && library_ptr[i].is_borrowed) {
            library_ptr[i].is_borrowed = 0;
            found = 1;
            printf("The book \"%s\" by %s is returned successfully.\n", 
                   library_ptr[i].title, library_ptr[i].author);
            break;
        } else if (library_ptr[i].id == id && !library_ptr[i].is_borrowed) {
            printf("The book \"%s\" is not currently borrowed.\n", library_ptr[i].title);
            return;
        }
    }

    if (!found) {
        printf("The book with ID %d is not found.\n", id);
    }
}
