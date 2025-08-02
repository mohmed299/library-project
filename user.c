// البحث عن الكتب (User Search)
#include "user.h"
#include <stdio.h>
#define MAX_RESULTS 100

Book searchResults[MAX_RESULTS];
int searchResultCount = 0;

void toLowerStr(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

//**************************Search By Title******************************//

void searchByTitle(){
    char search_title[100];
    printf("Enter the book title to search: ");
    fgets(search_title, sizeof(search_title), stdin);
    search_title[strcspn(search_title, "\n")] = 0;

    FILE *file = fopen(DATA_FILE, "r");
    if (!file) {
        printf("Error: Could not open %s\n", DATA_FILE);
        return;
    }

    Book book;
    int found = 0;
    searchResultCount = 0;

    char lower_search_title[100];
    strncpy(lower_search_title, search_title, sizeof(lower_search_title));
    lower_search_title[sizeof(lower_search_title) - 1] = '\0';
    toLowerStr(lower_search_title);

    while (fscanf(file, "%d|%[^|]|%[^|]|%d|%d\n",
                  &book.id, book.title, book.author,
                  &book.publication_year, &book.is_borrowed) == 5) {

        char lower_title[100];
        strncpy(lower_title, book.title, sizeof(lower_title));
        lower_title[sizeof(lower_title) - 1] = '\0';
        toLowerStr(lower_title);

        if (strstr(lower_title, lower_search_title)) {
            searchResults[searchResultCount++] = book;
            printf("\nID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nStatus: %s\n",
                   book.id, book.title, book.author,
                   book.publication_year,
                   book.is_borrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("No books found with title containing \"%s\".\n", search_title);
        return;
    }

    // Offer filter options
    int choice;
    printf("\nFilter search results:\n1. By Author\n2. By Year\n3. Exit\nChoice: ");
    scanf("%d", &choice);
    getchar(); // consume newline

    switch (choice) {
        case 1: filterByAuthor(); break;
        case 2: filterByYear(); break;
        case 3: default: break;
    }
}

//**************************filter By Author******************************//

void filterByAuthor(){
    char author[100];
    printf("Enter author's name to filter: ");
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

void filterByYear(){
    int year;
    printf("Enter publication year to filter: ");
    scanf("%d", &year);
    // getchar();  // consume newline after scanf (not used)

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
    Book b;
    FILE *fp = fopen("books.txt", "r");

    if (!fp) {
        printf("No books found, currently.\n");
        return;
    }

    printf("\nAvailable book list:\n");
    while (fread(&b, sizeof(Book), 1, fp)) {
        if (!b.is_borrowed) {
            printf("ID: %d | %s by %s (%d)\n", b.id, b.title, b.author, b.publication_year);
        }
    }

    fclose(fp);
}


void borrowBook() {
    int id, found = 0;
    Book b;

    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error occurred while opening files.\n");
        return;
    }

    printf("Enter the book ID you desire to borrow: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(Book), 1, fp)) {
        if (b.id == id && !b.is_borrowed) {
            b.is_borrowed = 1;
            found = 1;
        }
        fwrite(&b, sizeof(Book), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        printf("The book is borrowed successfully.\n");
    else
        printf("The book is not found or already borrowed.\n");
}


void returnBook() {
    int id, found = 0;
    Book b;

    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error occurred while opening files.\n");
        return;
    }

    printf("Enter the book ID you want to return: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(Book), 1, fp)) {
        if (b.id == id && b.is_borrowed) {
            b.is_borrowed = 0;
            found = 1;
        }
        fwrite(&b, sizeof(Book), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        printf("The book is returned successfully.\n");
    else
        printf("The book is not found or not borrowed.\n");
}



