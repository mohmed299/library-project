// البحث عن الكتب (User Search)
#include "user.h"
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

//**************************filter By Author******************************//

void filterByYear(){
    int year;
    printf("Enter publication year to filter: ");
    scanf("%d", &year);
    getchar();  // consume newline after scanf

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

void main(){

    searchByTitle();

}
