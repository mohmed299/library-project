#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "user.h"
#include "book.h"

// Admin credentials
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"
#define MAX_ATTEMPTS 3

// Declare external variables
extern Book library[MAX_BOOKS];
extern int book_count;

// Function to verify admin login
int admin_login() {
    char username[50];
    char password[50];
    int attempts = 0;
    
    printf("\n=== Admin Login ===\n");
    
    while (attempts < MAX_ATTEMPTS) {
        printf("Username: ");
        scanf("%s", username);
        
        printf("Password: ");
        scanf("%s", password);
        
        // Check credentials
        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("Login successful! Welcome, Admin.\n");
            return 1; // Success
        } else {
            attempts++;
            printf("Invalid credentials! Attempts remaining: %d\n", MAX_ATTEMPTS - attempts);
            
            if (attempts < MAX_ATTEMPTS) {
                printf("Please try again.\n\n");
            }
        }
    }
    
    printf("Maximum login attempts exceeded. Access denied.\n");
    return 0; // Failed
}

// Admin mode: simple menu for demonstration
void admin_mode() {
    // Check admin login first
    if (!admin_login()) {
        printf("Returning to main menu...\n");
        return;
    }
    
    int choice;
    
    do {
        printf("\n=== Admin Mode ===\n");
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
        
        if (choice != 6) {
            printf("\nPress Enter to continue...");
            clear_input_buffer();
            getchar();
        }
        
    } while (choice != 6);
}

// User mode: enhanced menu with ID-based borrowing features
void user_mode() {
    int choice;
    char user_id[NATIONAL_ID_LEN];
    
    // Initialize user pointers to access admin data
    init_user_pointers();
    
    do {
        printf("\n=== User Mode ===\n");
        printf("1. Search Book by Title\n");
        printf("2. View Available Books\n");
        printf("3. Borrow Book (Enter your National ID)\n");
        printf("4. Return Book (Enter your National ID)\n");
        printf("5. View My Borrowed Books (Enter your National ID)\n");
        printf("6. Search User by National ID\n");
        printf("7. Add New User\n");
        printf("8. Exit User Mode\n");
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
                printf("Enter your National ID: ");
                scanf("%s", user_id);
                display_user_borrowed_books_by_id(user_id);
                break;
            case 6:
                search_user_by_national_id();
                break;
            case 7:
                add_new_user();
                break;
            case 8:
                printf("Exiting User Mode...\n");
                break;
            default:
                invalid_choice();
                break;
        }
        
        if (choice != 8) {
            printf("\nPress Enter to continue...");
            clear_input_buffer();
            getchar();
        }
        
    } while (choice != 8);
}

void exiting_library() {
    printf("\n=== Thank you for using Library Management System ===\n");
    printf("Goodbye!\n");
    exit(0);
}

void invalid_choice() {
    printf("Invalid choice. Please try again.\n");
}

// Function to display welcome message
void display_welcome() {
    printf("\n========================================\n");
    printf("   LIBRARY MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("Welcome to the Digital Library!\n");
    printf("Choose your access level below:\n");
}

int main() {
    int choice;
    
    display_welcome();
    
    while (1) {
        printf("\n=== Main Menu ===\n");
        printf("1. Admin Mode (Login Required)\n");
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