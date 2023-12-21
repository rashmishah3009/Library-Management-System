#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100000
#define MAX_USERS 500

struct Book {
    int id;
    char title[100];
    char author[100];
    int quantity;
    int borrowed;
};

struct User {
    int id;
    char name[100];
    int borrowedBooks[MAX_BOOKS];
};

struct Book library[MAX_BOOKS];    //Array for storing books
struct User users[MAX_USERS];    //Array for storing users
int totalBooks = 0;    //Variable for counting total books
int totalUsers = 0;    //Variable for counting users

//Adding the books that are currently present in the library
void initializeLibrary() {
    struct Book defaultBooks[] = {
        {1, "The Immortals of Meluha", "Amish Tripathi", 5, 0},
        {2, "The Secret of the Nagas", "Amish Tripathi", 7, 0},
        {3, "The Oath of the Vayuputras", "Amish Tripathi", 4, 0}
    };

    int numDefaultBooks = sizeof(defaultBooks) / sizeof(defaultBooks[0]);

    //Counting books that are currently present in the library
    for (int i = 0; i < numDefaultBooks; ++i) {
        library[totalBooks++] = defaultBooks[i];
    }
}

//Function to add a new book
void addBook() {
    if (totalBooks >= MAX_BOOKS) {
        printf("Library capacity reached. Cannot add more books.\n");
        return;
    }

    struct Book newBook;
    printf("\nEnter book details:\n");
    printf("Book ID: ");
    scanf("%d", &newBook.id);

    printf("Book Title: ");
    scanf(" %[^\n]s", newBook.title);

    printf("Book Author: ");
    scanf(" %[^\n]s", newBook.author);

    printf("Quantity: ");
    scanf("%d", &newBook.quantity);
    newBook.borrowed = 0;    //Initially, no copies of the book are borrowed

    library[totalBooks++] = newBook;
    printf("\nBook added successfully!\n");
}

//Function to display all books present in the library
void displayBooks() {
    if (totalBooks == 0) {
        printf("\nNo books in the library.\n");
        return;
    }

    printf("\nBooks in the library:\n");
    printf("ID\tTitle\t\t\tAuthor\t\tQuantity\tAvailable\n");
    for (int i = 0; i < totalBooks; ++i) {
        printf("%d\t%-25s\t%-20s\t%d\t\t%d\n", library[i].id, library[i].title, library[i].author, library[i].quantity, (library[i].quantity - library[i].borrowed));
    }
}

//Function to borrow a book from the library
void borrowBook() {
    int userID;
    char bookTitle[100];
    int foundBook = 0;

    printf("\nEnter user ID: ");
    scanf("%d", &userID);
    getchar();

    printf("Enter book title to borrow: ");
    scanf(" %[^\n]", bookTitle);
    getchar();

    for (int i = 0; i < totalBooks; ++i) {
        if (strcmp(library[i].title, bookTitle) == 0) {
            foundBook = 1;
            if (library[i].borrowed < library[i].quantity) {
                library[i].borrowed++;
                users[userID - 1].borrowedBooks[users[userID - 1].id++] = library[i].id;
                printf("\nBook '%s' borrowed successfully by User %d\n", library[i].title, userID);
                return;
            } else {
                printf("\nSorry, all copies of '%s' are already borrowed.\n", library[i].title);
                return;
            }
        }
    }

    if (!foundBook) {
        printf("\nBook not found.\n");
    }
}

//Function to return a book to the library
void returnBook() {
    int bookID, userID;
    printf("\nEnter user ID: ");
    scanf("%d", &userID);

    printf("Enter book ID to return: ");
    scanf("%d", &bookID);

    for (int i = 0; i < totalBooks; ++i) {
        if (library[i].id == bookID) {
            if (library[i].borrowed > 0) {
                library[i].borrowed--;
                for (int j = 0; j < users[userID - 1].id; ++j) {
                    if (users[userID - 1].borrowedBooks[j] == bookID) {
                        users[userID - 1].borrowedBooks[j] = 0;
                        printf("\nBook '%s' returned successfully by User %d\n", library[i].title, userID);
                        return;
                    }
                }
                printf("\nUser %d did not borrow this book.\n", userID);
                return;
            } else {
                printf("\nNo copies of '%s' are currently borrowed.\n", library[i].title);
                return;
            }
        }
    }
    printf("\nBook ID not found.\n");
}

//Function to find a book
void findBook() {
    int searchID;
    char searchTitle[100];
    int found = 0;

    printf("\nSearch by Book ID (1) or Title (2): ");
    int searchChoice;
    scanf("%d", &searchChoice);

    if (searchChoice == 1) {
        printf("\nEnter Book ID: ");
        scanf("%d", &searchID);

        for (int i = 0; i < totalBooks; ++i) {
            if (library[i].id == searchID) {
                printf("\nBook ID: %d\n", library[i].id);
                printf("Book Title: %s\n", library[i].title);
                printf("Users who borrowed this book:\n");

                for (int j = 0; j < totalUsers; ++j) {
                    for (int k = 0; k < users[j].id; ++k) {
                        if (users[j].borrowedBooks[k] == searchID) {
                            printf("User ID: %d\n", users[j].id);
                            found = 1;
                            break;
                        }
                    }
                }

                if (!found) {
                    printf("No users have borrowed this book.\n");
                }
                return;
            }
        }
        printf("\nBook ID not found.\n");
    } else if (searchChoice == 2) {
        printf("\nEnter Book Title: ");
        scanf(" %[^\n]s", searchTitle);

        for (int i = 0; i < totalBooks; ++i) {
            if (strcmp(library[i].title, searchTitle) == 0) {
                printf("\nBook ID: %d\n", library[i].id);
                printf("Book Title: %s\n", library[i].title);
                printf("Users who borrowed this book:\n");

                for (int j = 0; j < totalUsers; ++j) {
                    for (int k = 0; k < users[j].id; ++k) {
                        if (users[j].borrowedBooks[k] == library[i].id) {
                            printf("User ID: %d\n", users[j].id);
                            found = 1;
                            break;
                        }
                    }
                }

                if (!found) {
                    printf("No users have borrowed this book.\n");
                }
                return;
            }
        }
        printf("\nBook Title not found.\n");
    } else {
        printf("\nInvalid choice.\n");
    }
}

int main() {

    initializeLibrary();    //Initialization of the library

    int choice;

    do {
        //Display menu and take user input
        printf("\n---------------------------------------------\n");
        printf("           Library Management System\n");
        printf("---------------------------------------------\n");
        printf("1. Add a book\n");
        printf("2. Display all books\n");
        printf("3. Borrow a book\n");
        printf("4. Return a book\n");
        printf("5. Find a book\n");
        printf("6. Exit\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        //Switch case based on user choice
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                findBook();
                break;
            case 6:
                printf("\nExiting the program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);    //Exit loop when the user chooses to exit

    return 0;
}
