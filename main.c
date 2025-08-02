#include <stdlib.h> // For system()
#include <stdlib.h>

#include "book.h"         // Includes Book structure and utility functions
#include "admin.h"        // Includes Admin Mode function declarations
#include "user.h"         // Includes User Mode function declarations
#include "data_handler.h" // Includes data loading/saving function declarations

#define DATA_FILE "library_books.txt"

int main() {
    Book library[MAX_BOOKS];
    int book_count = 0;

    printf("Initializing library...\n");

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
                admin_mode(library, &book_count); // Call Admin Mode function
                break;
            case 2:
                //user_mode(library, &book_count);  // Call User Mode function
                break;
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
