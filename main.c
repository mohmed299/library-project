#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
#include "user.h"
#include "book.h"

// Declare external variables
extern Book library[MAX_BOOKS];
extern int book_count;

// Admin mode: simple menu for demonstration
void admin_mode() {
    int choice;
    printf("Entering Admin Mode...\n");
    printf("1. Add Book\n");
    printf("2. Remove Book\n");
    printf("3. View All Books\n");
    printf("4. Count Total Books\n");
    printf("5. View Borrowed Books\n");
    printf("6. Exit Admin Mode\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            removeBook();
            break;
        case 3:
            view_all_books(library, book_count);
            break;
        case 4:
            countTotalBooks();
            break;
        case 5:
            view_borrowed_books(library, book_count);
            break;
        case 6:
            printf("Exiting Admin Mode...\n");
            break;
        default:
            invalid_choice();
            break;
    }
}

// User mode: simple menu for demonstration
void user_mode() {
    int choice;
    printf("Entering User Mode...\n");
    printf("1. Search Book\n");
    printf("2. View Available Books\n");
    printf("3. Borrow Book\n");
    printf("4. Return Book\n");
    printf("5. Exit User Mode\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            searchByTitle();
            break;
        case 2:
            viewAvailableBooks();
            break;
        case 3:
            borrowBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            printf("Exiting User Mode...\n");
            break;
        default:
            invalid_choice();
            break;
    }
}

void exiting_library() {
    printf("Exiting Library System. Goodbye!\n");
    exit(0);
}

void invalid_choice() {
    printf("Invalid choice. Please try again.\n");
}

int main() {
    int choice;
    
    printf("Welcome to the Library Management System!\n");
    
    while (1) {
        printf("\nMain Menu:\n");
        printf("1. Admin Mode\n");
        printf("2. User Mode\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                admin_mode();
                break;
            case 2:
                user_mode();
                break;
            case 3:
                exiting_library();
                break;
            default:
                invalid_choice();
                break;
        }
    }
    
    return 0;
}
