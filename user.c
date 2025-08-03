#include "user.h"



static Book *library_ptr = NULL;
static int *book_count_ptr = NULL;
static int *next_id_ptr = NULL;


User users[MAX_USERS];
int user_count = 0;

Book searchResults[MAX_RESULTS];
int searchResultCount = 0;


void init_user_pointers() {
    library_ptr = get_library_address();
    book_count_ptr = get_book_count_address();
    next_id_ptr = get_next_id_address();
    
    
    load_users_from_file();
}

void toLowerStr(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

//**************************National ID Functions******************************//

// Find user by national ID
int find_user_by_national_id(const char *national_id) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].national_id, national_id) == 0) {
            return i; // Return index if found
        }
    }
    return -1; // Not found
}

// Display user information
void display_user_info(const User *user) {
    printf("\n=== User Information ===\n");
    printf("National ID: %s\n", user->national_id);
    printf("Name: %s\n", user->name);
    printf("Phone: %s\n", user->phone);
    printf("Email: %s\n", user->email);
    printf("Books Borrowed: %d\n", user->books_borrowed);
    
    if (user->books_borrowed > 0) {
        printf("Borrowed Book IDs: ");
        for (int i = 0; i < user->books_borrowed; i++) {
            printf("%d", user->borrowed_book_ids[i]);
            if (i < user->books_borrowed - 1) printf(", ");
        }
        printf("\n");
        
        // Display actual book details
        printf("\nBorrowed Books Details:\n");
        for (int i = 0; i < user->books_borrowed; i++) {
            int book_id = user->borrowed_book_ids[i];
            // Find book in library
            for (int j = 0; j < *book_count_ptr; j++) {
                if (library_ptr[j].id == book_id) {
                    printf("- \"%s\" by %s (ID: %d)\n", 
                           library_ptr[j].title, 
                           library_ptr[j].author, 
                           library_ptr[j].id);
                    break;
                }
            }
        }
    }
    printf("========================\n");
}

// Display borrowed books by specific user ID
void display_user_borrowed_books_by_id(const char *user_id) {
    int user_index = find_user_by_national_id(user_id);
    
    if (user_index == -1) {
        printf("User with National ID '%s' not found.\n", user_id);
        return;
    }
    
    User *user = &users[user_index];
    
    printf("\n=== Books Borrowed by %s (ID: %s) ===\n", user->name, user->national_id);
    printf("Total books borrowed: %d\n", user->books_borrowed);
    
    if (user->books_borrowed == 0) {
        printf("No books currently borrowed.\n");
        printf("================================\n");
        return;
    }
    
    printf("\nBorrowed Books:\n");
    for (int i = 0; i < user->books_borrowed; i++) {
        int book_id = user->borrowed_book_ids[i];
        // Find book in library
        for (int j = 0; j < *book_count_ptr; j++) {
            if (library_ptr[j].id == book_id) {
                printf("%d. \"%s\" by %s (Year: %d) [ID: %d]\n", 
                       i + 1,
                       library_ptr[j].title, 
                       library_ptr[j].author,
                       library_ptr[j].publication_year,
                       library_ptr[j].id);
                break;
            }
        }
    }
    printf("================================\n");
}

// Add new user
void add_new_user() {
    if (user_count >= MAX_USERS) {
        printf("Maximum number of users reached!\n");
        return;
    }
    
    User new_user;
    
    printf("\n=== Add New User ===\n");
    
    printf("Enter National ID: ");
    scanf("%s", new_user.national_id);
    
    // Check if user already exists
    if (find_user_by_national_id(new_user.national_id) != -1) {
        printf("User with National ID %s already exists!\n", new_user.national_id);
        return;
    }
    
    clear_input_buffer();
    
    printf("Enter Full Name: ");
    fgets(new_user.name, MAX_NAME_LEN, stdin);
    new_user.name[strcspn(new_user.name, "\n")] = 0;
    
    printf("Enter Phone Number: ");
    scanf("%s", new_user.phone);
    
    printf("Enter Email: ");
    scanf("%s", new_user.email);
    
    // Initialize borrowing information
    new_user.books_borrowed = 0;
    for (int i = 0; i < 10; i++) {
        new_user.borrowed_book_ids[i] = 0;
    }
    
    // Add user to array
    users[user_count] = new_user;
    user_count++;
    
    // Save to file
    save_users_to_file();
    
    printf("User added successfully!\n");
    display_user_info(&new_user);
}

// Search user by national ID
void search_user_by_national_id() {
    char national_id[NATIONAL_ID_LEN];
    
    printf("\n== Search User by National ID ==\n");
    printf("Enter National ID: ");
    scanf("%s", national_id);
    
    int index = find_user_by_national_id(national_id);
    
    if (index != -1) {
        printf("User Found!\n");
        display_user_info(&users[index]);
    } else {
        printf("User with National ID '%s' not found.\n", national_id);
        
        char choice;
        printf("Would you like to add this user? (y/n): ");
        scanf(" %c", &choice);
        
        if (choice == 'y' || choice == 'Y') {
            // Pre-fill the national ID for new user
            if (user_count < MAX_USERS) {
                User new_user;
                strcpy(new_user.national_id, national_id);
                
                clear_input_buffer();
                
                printf("Enter Full Name: ");
                fgets(new_user.name, MAX_NAME_LEN, stdin);
                new_user.name[strcspn(new_user.name, "\n")] = 0;
                
                printf("Enter Phone Number: ");
                scanf("%s", new_user.phone);
                
                printf("Enter Email: ");
                scanf("%s", new_user.email);
                
                // Initialize borrowing information
                new_user.books_borrowed = 0;
                for (int i = 0; i < 10; i++) {
                    new_user.borrowed_book_ids[i] = 0;
                }
                
                // Add user to array
                users[user_count] = new_user;
                user_count++;
                
                // Save to file
                save_users_to_file();
                
                printf("User added successfully!\n");
                display_user_info(&new_user);
            } else {
                printf("Cannot add user - maximum limit reached!\n");
            }
        }
    }
}

// Save users to file
void save_users_to_file() {
    FILE *file = fopen(USERS_FILE, "w");
    if (!file) {
        printf("Error: Could not save users to file.\n");
        return;
    }
    
    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%s|%s|%s|%s|%d",
                users[i].national_id,
                users[i].name,
                users[i].phone,
                users[i].email,
                users[i].books_borrowed);
        
        // Save borrowed book IDs
        for (int j = 0; j < users[i].books_borrowed; j++) {
            fprintf(file, "|%d", users[i].borrowed_book_ids[j]);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
}

// Load users from file
void load_users_from_file() {
    FILE *file = fopen(USERS_FILE, "r");
    if (!file) {
        // File doesn't exist yet, that's okay
        user_count = 0;
        return;
    }
    
    user_count = 0;
    char line[500];
    
    while (fgets(line, sizeof(line), file) && user_count < MAX_USERS) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        // Parse the line
        char *token = strtok(line, "|");
        if (!token) continue;
        
        strcpy(users[user_count].national_id, token);
        
        token = strtok(NULL, "|");
        if (!token) continue;
        strcpy(users[user_count].name, token);
        
        token = strtok(NULL, "|");
        if (!token) continue;
        strcpy(users[user_count].phone, token);
        
        token = strtok(NULL, "|");
        if (!token) continue;
        strcpy(users[user_count].email, token);
        
        token = strtok(NULL, "|");
        if (!token) continue;
        users[user_count].books_borrowed = atoi(token);
        
        // Initialize borrowed book IDs array
        for (int i = 0; i < 10; i++) {
            users[user_count].borrowed_book_ids[i] = 0;
        }
        
        // Load borrowed book IDs
        for (int i = 0; i < users[user_count].books_borrowed; i++) {
            token = strtok(NULL, "|");
            if (token) {
                users[user_count].borrowed_book_ids[i] = atoi(token);
            }
        }
        
        user_count++;
    }
    
    fclose(file);
    printf("Loaded %d users from file.\n", user_count);
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

// Enhanced borrowing function with user ID tracking
void borrowBook() {
    // Initialize pointers if not done already
    if (library_ptr == NULL) {
        init_user_pointers();
    }

    if (*book_count_ptr == 0) {
        printf("No books in the library.\n");
        return;
    }

    char user_id[NATIONAL_ID_LEN];
    int book_id;
    
    printf("\n=== Borrow Book ===\n");
    
    // Get user ID
    printf("Enter your National ID: ");
    scanf("%s", user_id);
    
    // Find user by ID
    int user_index = find_user_by_national_id(user_id);
    if (user_index == -1) {
        printf("User with National ID '%s' not found in the system.\n", user_id);
        printf("Please register first or contact an administrator.\n");
        return;
    }
    
    // Check if user has reached borrowing limit
    if (users[user_index].books_borrowed >= 10) {
        printf("You have reached the maximum borrowing limit (10 books).\n");
        printf("Please return some books before borrowing new ones.\n");
        return;
    }
    
    printf("Enter the book ID you want to borrow: ");
    scanf("%d", &book_id);

    // Find the book
    int book_found = 0;
    for (int i = 0; i < *book_count_ptr; i++) {
        if (library_ptr[i].id == book_id) {
            book_found = 1;
            if (library_ptr[i].is_borrowed) {
                printf("The book \"%s\" is already borrowed.\n", library_ptr[i].title);
                return;
            }
            
            // Mark book as borrowed
            library_ptr[i].is_borrowed = 1;
            
            // Add book to user's borrowed list
            users[user_index].borrowed_book_ids[users[user_index].books_borrowed] = book_id;
            users[user_index].books_borrowed++;
            
            // Save users to file
            save_users_to_file();
            
            printf("Book \"%s\" by %s successfully borrowed by %s (ID: %s).\n", 
                   library_ptr[i].title, library_ptr[i].author, users[user_index].name, users[user_index].national_id);
            printf("You now have %d book(s) borrowed.\n", users[user_index].books_borrowed);
            break;
        }
    }

    if (!book_found) {
        printf("Book with ID %d not found.\n", book_id);
    }
}

// Enhanced return function with user ID tracking
void returnBook() {
    // Initialize pointers if not done already
    if (library_ptr == NULL) {
        init_user_pointers();
    }

    if (*book_count_ptr == 0) {
        printf("No books in the library.\n");
        return;
    }

    char user_id[NATIONAL_ID_LEN];
    int book_id;
    
    printf("\n=== Return Book ===\n");
    
    // Get user ID
    printf("Enter your National ID: ");
    scanf("%s", user_id);
    
    // Find user
    int user_index = find_user_by_national_id(user_id);
    if (user_index == -1) {
        printf("User with National ID '%s' not found in the system.\n", user_id);
        return;
    }
    
    // Show user's borrowed books
    if (users[user_index].books_borrowed == 0) {
        printf("You have no books to return.\n");
        return;
    }
    
    printf("\nYour borrowed books (%s):\n", users[user_index].name);
    for (int i = 0; i < users[user_index].books_borrowed; i++) {
        int book_id_temp = users[user_index].borrowed_book_ids[i];
        // Find book details
        for (int j = 0; j < *book_count_ptr; j++) {
            if (library_ptr[j].id == book_id_temp) {
                printf("%d. \"%s\" by %s (ID: %d)\n", 
                       i + 1, library_ptr[j].title, library_ptr[j].author, book_id_temp);
                break;
            }
        }
    }
    
    printf("\nEnter the book ID you want to return: ");
    scanf("%d", &book_id);

    // Check if user has this book
    int user_book_index = -1;
    for (int i = 0; i < users[user_index].books_borrowed; i++) {
        if (users[user_index].borrowed_book_ids[i] == book_id) {
            user_book_index = i;
            break;
        }
    }
    
    if (user_book_index == -1) {
        printf("You have not borrowed book with ID %d.\n", book_id);
        return;
    }

    // Find the book in library and mark as returned
    int book_found = 0;
    for (int i = 0; i < *book_count_ptr; i++) {
        if (library_ptr[i].id == book_id) {
            book_found = 1;
            library_ptr[i].is_borrowed = 0;
            
            printf("Book \"%s\" by %s successfully returned by %s (ID: %s).\n", 
                   library_ptr[i].title, library_ptr[i].author, users[user_index].name, users[user_index].national_id);
            break;
        }
    }
    
    if (book_found) {
        // Remove book from user's borrowed list
        for (int i = user_book_index; i < users[user_index].books_borrowed - 1; i++) {
            users[user_index].borrowed_book_ids[i] = users[user_index].borrowed_book_ids[i + 1];
        }
        users[user_index].books_borrowed--;
        users[user_index].borrowed_book_ids[users[user_index].books_borrowed] = 0;
        
        // Save users to file
        save_users_to_file();
        
        printf("You now have %d book(s) borrowed.\n", users[user_index].books_borrowed);
    } else {
        printf("Book with ID %d not found in library.\n", book_id);
    }
}