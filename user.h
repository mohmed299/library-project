#ifndef USER_H
#define USER_H

#include <string.h>   // For: strcspn, strncpy, strstr
#include <ctype.h>    // For: tolower
#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#include "admin.h"

#define MAX_RESULTS 100
#define USERS_FILE "users.txt"


#define MAX_USERS 1000
#define MAX_NAME_LEN 100
#define NATIONAL_ID_LEN 15
#define PHONE_LEN 20
#define EMAIL_LEN 50


// User structure for national ID management
typedef struct {
    char national_id[NATIONAL_ID_LEN];
    char name[MAX_NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
    int books_borrowed;
    int borrowed_book_ids[10]; // Maximum 10 books per user
} User;

// Function declarations 
void viewAvailableBooks();
void borrowBookByUser();
void returnBookByUser();
void searchByTitle();
void filterByAuthor();
void filterByYear();
void toLowerStr(char *str);
void init_user_pointers();

// National ID functions
int find_user_by_national_id(const char *national_id);
void add_new_user();
void search_user_by_national_id();
void display_user_info(const User *user);
void display_user_borrowed_books_by_id(const char *user_id);
void save_users_to_file();
void load_users_from_file();


void borrowBook();
void returnBook();

#endif