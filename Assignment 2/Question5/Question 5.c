/**
 *Programmer: Siraj Mughal
 *Class: BDS-1A
 *Roll No: 26K-2564
 *Program: library system
 *Date:27/Oct/2026
 *Desc: Acts like a library system, a member can register, view books, borrow and return books, 
       and also pay a fine if you are late.
 */




// Before looking the program please make sure all the ids are of type int, thanks, if u were to type a string it will carry out a infine loop.

#include <stdio.h>
#include <string.h>

void displayMenu() {
    printf("\n1. Register member\n2. Display books\n3. Borrow a book\n4. Return a book\n");
    printf("5. Display member record\n6. Exit\nEnter your choice: ");
}

// memberType: 1 = Student, 2 = Faculty
void registerMember(char name[], int *studentID, int *memberType) {
    printf("Enter name: ");
    scanf(" %49[^\n]", name);
    printf("Enter student ID: ");
    scanf("%d", studentID);

    *memberType = 0;
    while (*memberType != 1 && *memberType != 2) {
        printf("Enter membership type (1 = Student, 2 = Faculty): ");
        scanf("%d", memberType);
        if (*memberType != 1 && *memberType != 2) {
            printf("Invalid membership type.\n");
        }
    }
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    int i; // i is the book

    printf("\nID     Title                     Copies\n");
    for (i = 0; i < totalBooks; i++) {
        printf("%-6d %-25s %d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount, int memberType) {
    int id;        // book id the user typed
    int days = 0;  // days they want to keep it
    int i;         // i is the book
    int pos = -1;  // where the book is in the list

    if (*borrowedCount == 3) {
        printf("You already have 3 books.\n");
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &id);
    for (i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("Invalid book ID.\n");
        return;
    }
    if (availableCopies[pos] == 0) {
        printf("No copies available.\n");
        return;
    }

    while (days <= 0) {
        printf("Enter days you want to keep it: ");
        scanf("%d", &days);
        if (days <= 0) {
            printf("Days must be positive.\n");
        }
    }
    if ((memberType == 1 && days > 14) || (memberType == 2 && days > 30)) {
        printf("Note: a fine applies after the allowed days.\n");
    }

    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[pos]--;
    printf("You borrowed %s.\n", bookTitles[pos]);
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks,
                 int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine) {
    int id;             // book id the user typed
    int days = 0;       // days it was kept
    int i;              // i goes through the borrowed list
    int j;              // j goes through the books
    int pos = -1;       // where it is in the borrowed list
    int stock = -1;     // where it is in the books
    int allowed = 30;   // allowed days
    int rate = 10;      // fine for each extra day
    float fine = 0;
    char code[20];

    if (memberType == 1) {
        allowed = 14;
        rate = 20;
    }

    printf("Enter book ID to return: ");
    scanf("%d", &id);
    for (i = 0; i < *borrowedCount; i++) {
        if (borrowedBookIDs[i] == id) {
            pos = i;
        }
    }
    if (pos == -1) {
        printf("You have not borrowed this book.\n");
        return 0;
    }
    for (j = 0; j < totalBooks; j++) {
        if (bookIDs[j] == id) {
            stock = j;
        }
    }

    while (days <= 0) {
        printf("Enter days the book was kept: ");
        scanf("%d", &days);
        if (days <= 0) {
            printf("Days must be positive.\n");
        }
    }
    availableCopies[stock]++;

    if (days > allowed) {
        fine = (days - allowed) * rate;
        *totalFine = *totalFine + fine;
        printf("Late return. Fine: Rs. %.2f\n", fine);
        printf("Enter membership code: ");
        scanf("%19s", code);
        if (strcmp(code, "LIB2026") == 0) {
            fine = fine / 2;
            printf("50%% waiver applied.\n");
        }
        printf("Fine payable: Rs. %.2f\n", fine);
    } else {
        printf("Returned on time, no fine.\n");
    }

    // remove it from the borrowed list by moving the rest one step left
    for (i = pos; i < *borrowedCount - 1; i++) {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }
    (*borrowedCount)--;
    return fine;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[],
                         int borrowedCount, float totalFine, float fineAfterWaiver) {
    int i; // i goes through the borrowed list

    printf("\nName: %s\nStudent ID: %d\n", name, studentID);
    if (memberType == 1) {
        printf("Membership type: Student\n");
    } else {
        printf("Membership type: Faculty\n");
    }
    printf("Borrowed books: ");
    for (i = 0; i < borrowedCount; i++) {
        printf("%d ", borrowedBookIDs[i]);
    }
    printf("\nTotal fine before waiver: Rs. %.2f\n", totalFine);
    printf("Final fine payable: Rs. %.2f\n", fineAfterWaiver);
}

int main() {
    int bookIDs[4] = {101, 102, 103, 104};
    char bookTitles[4][50] = {"Programming in C", "Data Structures", "Database Systems", "Computer Networks"};
    int availableCopies[4] = {5, 3, 0, 4};
    char name[50];
    int studentID = 0;
    int memberType = 0; // 1 = Student, 2 = Faculty
    int borrowedBookIDs[3];
    int borrowedCount = 0;
    float totalFine = 0;       // fine before waivers
    float fineAfterWaiver = 0;
    int registered = 0;        // 1 after registering
    int choice = 0;

    while (choice != 6) {
        displayMenu();
        scanf("%d", &choice);

        if (choice >= 3 && choice <= 5 && registered == 0) {
            printf("Please register first.\n");
            continue;
        }

        switch (choice) {
        case 1:
            if (registered == 1) {
                printf("A member is already registered.\n");
            } else {
                registerMember(name, &studentID, &memberType);
                registered = 1;
            }
            break;
        case 2:
            displayBooks(bookIDs, bookTitles, availableCopies, 4);
            break;
        case 3:
            borrowBook(bookIDs, bookTitles, availableCopies, 4, borrowedBookIDs, &borrowedCount, memberType);
            break;
        case 4:
            fineAfterWaiver = fineAfterWaiver + returnBook(bookIDs, availableCopies, 4,
                              borrowedBookIDs, &borrowedCount, memberType, &totalFine);
            break;
        case 5:
            displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
            break;
        case 6:
            printf("Goodbye.\n");
            break;
        default:
            printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}
