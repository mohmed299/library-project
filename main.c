#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#include "admin.h"
#include "user.h"

#define DATA_FILE "library_books.txt"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Book library[MAX_BOOKS];
    int book_count = 0;

    int choice;
    do {
        system("cls || clear");

        printf("\n--- Library Book Tracking System ---\n");
        printf("1. Admin Mode\n");
        printf("2. User Mode\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        clear_input_buffer();

        switch (choice) {
            case 1:
                system("cls || clear");
                printf("=== Admin Mode ===\n");
                view_all_books(library, book_count);
                break;

            case 2: {
                system("cls || clear");
                printf("=== User Mode ===\n");

                int user_choice;
                do {
                    printf("\nUser Menu:\n");
                    printf("1. View Available Books\n");
                    printf("2. Borrow a Book\n");
                    printf("3. Return a Book\n");
                    printf("4. Search by Title\n");
                    printf("5. Filter by Author\n");
                    printf("6. Filter by Year\n");
                    printf("7. Back to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &user_choice);
                    clear_input_buffer();

                    switch(user_choice) {
                        case 1: viewAvailableBooks(); break;
                        case 2: borrowBook(); break;
                        case 3: returnBook(); break;
                        case 4: searchByTitle(); break;
                        case 5: filterByAuthor(); break;
                        case 6: filterByYear(); break;
                        case 7: printf("Returning to Main Menu...\n"); break;
                        default: printf("Invalid input\n"); break;
                    }

                    if (user_choice != 7) {
                        printf("Press Enter to continue...");
                        clear_input_buffer();
                    }

                } while(user_choice != 7);
                break;
            }

            case 3:
                printf("Exiting Library System. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        if (choice != 3) {
            printf("Press Enter to continue...");
            clear_input_buffer();
        }

    } while (choice != 3);

    return 0;
}
