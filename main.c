#include <stdio.h>
#include <stdlib.h> // For system()

#include "book.h"         // Includes Book structure and utility functions
#include "admin.h"        // Includes Admin Mode function declarations
#include "user.h"         // Includes User Mode function declarations
#include "data_handler.h" // Includes data loading/saving function declarations

// Define the filename for storing book data
#define DATA_FILE "library_books.txt"

// Main function - entry point of the program
int main() {
    Book library[MAX_BOOKS]; // Array to store book data
    int book_count = 0;      // Current number of books in the library

    // Load book data when the program starts
    if (load_books(DATA_FILE, library, &book_count)) {
        printf("Books loaded successfully from %s. Total books: %d\n", DATA_FILE, book_count);
    } else {
        printf("No existing book data found or error loading. Starting with empty library.\n");
    }

    int choice;
    do {
        system("cls || clear"); // Clear the console screen (cross-platform)
        printf("\n--- Library Book Tracking System ---\n");
        printf("1. Admin Mode\n");
        printf("2. User Mode\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clear_input_buffer(); // Clear any leftover characters in the input buffer

        switch (choice) {
            case 1:
                admin_mode(library, &book_count); // Call Admin Mode function
                break;
            case 2:
                user_mode(library, &book_count);  // Call User Mode function
                break;
            case 3:
                printf("Exiting Library System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                printf("Press Enter to continue...");
                clear_input_buffer();
                break;
        }
    } while (choice != 3); // Loop until user chooses to exit

    return 0; // Indicate successful program execution
}
