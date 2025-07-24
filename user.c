// البحث عن الكتب (User Search)
#include "user.h"

void toLowerStr(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

void searchByTitle() {
    char search_title[100];
    char lower_search_title[100];

    printf("Enter the book title to search: ");
    fgets(search_title, sizeof(search_title), stdin);

    // Remove trailing newline from fgets
    search_title[strcspn(search_title, "\n")] = 0;

    FILE *file = fopen(DATA_FILE, "r");
    if (!file) {
        printf("Error: Could not open %s\n", DATA_FILE);
        return;
    }

    Book book;

    strncpy(lower_search_title, search_title, sizeof(lower_search_title));
    lower_search_title[sizeof(lower_search_title) - 1] = '\0';
    toLowerStr(lower_search_title);

    int found = 0;
    while (fscanf(file, "%d|%[^|]|%[^|]|%d|%d\n",
                  &book.id,
                  book.title,
                  book.author,
                  &book.publication_year,
                  &book.is_borrowed) == 5) {

        char lower_title[100];
        strncpy(lower_title, book.title, sizeof(lower_title));
        lower_title[sizeof(lower_title) - 1] = '\0';
        toLowerStr(lower_title);

        if (strstr(lower_title, lower_search_title)) {
            printf("\nBook Found:\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nStatus: %s\n",
                   book.id,
                   book.title,
                   book.author,
                   book.publication_year,
                   book.is_borrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }

    if (!found) {
        printf("No book found with title containing \"%s\".\n", search_title);
    }

    fclose(file);
}

int main(void){
    searchByTitle();

    return 0;
}
